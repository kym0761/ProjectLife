// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkComponent.h"
#include "LinkEdge.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LinkHold.h"
#include "LinkTrigger.h"
#include "PuzzleTrigger.h"


// Sets default values for this component's properties
ULinkComponent::ULinkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionProfileName(TEXT("LinkOverlap"));

	// ...
	bRootLink = false;
	bLinkActivated = false;
	
	InitCapsuleSize(500.0f,750.0f);
	ShapeColor = FColor::Blue;

}


// Called when the game starts
void ULinkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//If RootLink, Activate Owner.
	if (bRootLink)
	{
		bLinkActivated = true;
		ALinkTrigger* owner = Cast<ALinkTrigger>(GetOwner());
		if (IsValid(owner))
		{
			owner->bTriggerActive = bLinkActivated;
		}
	}

	OnComponentBeginOverlap.AddDynamic(this, &ULinkComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ULinkComponent::OnEndOverlap);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(LinkTimer, this, &ULinkComponent::LinkJob, LinkJobInterval, true);
	}
	

}


// Called every frame
void ULinkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

bool ULinkComponent::GetLinkActivate() const
{
	return bLinkActivated;
}

void ULinkComponent::SetLinkActivate(bool InVal)
{
	//if RootLink, Don't Change Anything.
	if (!bRootLink)
	{
		bLinkActivated = InVal;

		ALinkTrigger* owner= Cast<ALinkTrigger>(GetOwner());
		if (IsValid(owner))
		{
			owner->SetTriggerActivate(bLinkActivated);
		}
	}
}

bool ULinkComponent::CheckLinkedWithRoot()
{
	if (bRootLink)
	{
		return true;
	}

	bool result = false;

	//Array for Traversing
	TArray<ULinkComponent*> ElectricComp;
	
	//Cache for Already Traversed.
	TArray<ULinkComponent*> ElectricCompRemember;
	TArray<ALinkEdge*> ElectricEdgeRemember;

	//first, Add Self.
	ElectricComp.Add(this);
	ElectricCompRemember.AddUnique(this);

	while (ElectricComp.Num() > 0)
	{

		ULinkComponent* popResult = ElectricComp.Pop();

		if (IsValid(popResult))
		{
			for (ALinkEdge* i : popResult->LinkEdges)
			{

				//find Edge which is Currently Not Traversed.
				bool bIsIn = ElectricEdgeRemember.Find(i) == -1 ? false : true;
				if (bIsIn == false)
				{
					//Add Traversed Edge.
					ElectricEdgeRemember.AddUnique(i);

					if (!(LinkComps.IsValidIndex(0) && LinkComps.IsValidIndex(1)))
					{
						return false;
					}

					//Check whether Comp1 is Traversed or not. 
					ULinkComponent* comp1 = i->LinkComps[0];
					if (IsValid(comp1))
					{
						//if RootLink Found, return true.
						if (comp1->bRootLink)
						{
							return true;
						}

						bool bIsComp1_In = ElectricCompRemember.Find(comp1) == -1 ? false : true;
						if (bIsComp1_In == false)
						{
							ElectricComp.Add(i->LinkComps[0]);
							ElectricCompRemember.AddUnique(i->LinkComps[0]);
						}
					}

					//Check whether Comp2 is Traversed or not.
					ULinkComponent* comp2 = i->LinkComps[1];
					if (IsValid(comp2))
					{
						//if RootLink Found, return true. 
						if (comp2->bRootLink)
						{
							return true;
						}

						bool bIsComp2_In = ElectricCompRemember.Find(comp2) == -1 ? false : true;
						if (bIsComp2_In == false)
						{
							ElectricComp.Add(i->LinkComps[1]);
							ElectricCompRemember.AddUnique(i->LinkComps[1]);
						}
					}
				}
			}
		}
	}

	return result;
}

bool ULinkComponent::CheckEdgeCanExist(ULinkComponent* OtherLinkComp)
{
	
	if (!IsValid(OtherLinkComp))
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Other Link Component Not Valid"));
		return false;
	}

	//Check One of them is Active.
	//then Check there is Any Obstacles Between them.
	if (GetLinkActivate() || OtherLinkComp->GetLinkActivate())
	{
		TArray<AActor*> ignores;

		//ignore Collision of Owner Actors
		TArray<AActor*> arr1;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALinkTrigger::StaticClass(), arr1);
		TArray<AActor*> arr2;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALinkHold::StaticClass(), arr2);
		ignores.Append(arr1);
		ignores.Append(arr2);

		//Set Trace Type
		TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
		objectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		objectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

		FHitResult hit;

		bool result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			GetComponentLocation(),
			OtherLinkComp->GetComponentLocation(),
			objectType,
			false,
			ignores,
			EDrawDebugTrace::None,
			//EDrawDebugTrace::ForOneFrame,
			//EDrawDebugTrace::ForDuration,
			hit,
			true,
			FLinearColor::Red,FLinearColor::Green,0.5f
		);

		//If There isn't Any Collision, Edge Can Exist.
		if (result == false)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s is Success.  ----- Other : %s"), *GetOwner()->GetName(), *OtherLinkComp->GetOwner()->GetName());
			return true;
		}
	}

	//Trace failed or obstacles detected.
	return false;

}

void ULinkComponent::TrySpawnEdge(ULinkComponent* OtherLinkComp)
{
	bool bConnectionExist = false;

	//Other Not Valid, Cancel.
	if (!IsValid(OtherLinkComp))
	{
		return;
	}

	//Root Not Linked, Cancel.
	if (!CheckLinkedWithRoot())
	{
		return;
	}

	//Check All LinkEdges which Has "OtherLinkComp" already Exist.
	for (ALinkEdge* i : LinkEdges)
	{
		bool temp = i->LinkComps.Find(OtherLinkComp) != -1 ? true : false;
		if (temp)
		{
			bConnectionExist = true;
			break;
		}
	}

	//there is not connection, Spawn Edge.
	if (!bConnectionExist)
	{
		if (LinkEdgeClass)
		{
			ALinkEdge* edge = GetWorld()->SpawnActorDeferred<ALinkEdge>(LinkEdgeClass, GetComponentTransform(),nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (IsValid(edge))
			{
				edge->InitializeCompRefs(this,OtherLinkComp);
				edge->FinishSpawning(GetComponentTransform());
				LinkEdges.Add(edge);
				
				OtherLinkComp->LinkEdges.Add(edge);
				OtherLinkComp->SetLinkActivate(true);

				AdjacentLinkComps.Add(OtherLinkComp);
				OtherLinkComp->AdjacentLinkComps.Add(this);
			}
		}
	}


}

void ULinkComponent::TryRemoveEdge(ULinkComponent* OtherLinkComp)
{
	//find Edge that Link "this" and "OtherLinkComp".
	int index1 = -1, index2 = -1;
	for (int32 i = 0; i < LinkEdges.Num(); i++)
	{
		bool found = LinkEdges[i]->LinkComps.Find(OtherLinkComp) != -1 ? true : false;
		if (found)
		{
			index1 = i;
			break;
		}
	}

	for (int32 i = 0; i < OtherLinkComp->LinkEdges.Num(); i++)
	{
		bool found = OtherLinkComp->LinkEdges[i]->LinkComps.Find(this) != -1 ? true : false;
		if (found)
		{
			index2 = i;
			break;
		}
	}

	//if not Found, End Function.
	if (index1 == -1 || index2 == -1)
	{
		return;
	}

	//get Ref of Edge that want to remove
	ALinkEdge* edgeToRemove = LinkEdges[index1];

	//Remove Edge Ref In Ref Arrays.
	LinkEdges.RemoveAt(index1);
	OtherLinkComp->LinkEdges.RemoveAt(index2);

	//Remove Adjacent Component Each Of Them.
	AdjacentLinkComps.Remove(OtherLinkComp);
	OtherLinkComp->AdjacentLinkComps.Remove(this);

	//destroy actor.
	edgeToRemove->Destroy();


	//Re-Evaluate each of LinkComponents that has linked with Root.
	ReEvaluateAllLinks();
	OtherLinkComp->ReEvaluateAllLinks();
}

void ULinkComponent::TryRemoveAllEdges()
{
	for (ULinkComponent* i : LinkComps)
	{
		TryRemoveEdge(i);
	}
}

void ULinkComponent::FindAllOtherLinkComps()
{
	////find Other Link Components Except "this"
	//reset Current LinkCompArray.
	LinkComps.Empty();

	TArray<AActor*> actors;
	GetOverlappingActors(actors, AActor::StaticClass());

	for (AActor* i : actors)
	{
		//skip self.
		if (i == GetOwner())
		{
			continue;
		}

		ULinkComponent* linkComp = i->FindComponentByClass<ULinkComponent>();
		if (IsValid(linkComp))
		{
			LinkComps.Add(linkComp);
		}
	}

}

void ULinkComponent::ReEvaluateAllLinks()
{
	bool result = CheckLinkedWithRoot();
	if (result == false)
	{
		SetLinkActivate(false);
	}
}

void ULinkComponent::LinkJob()
{
	if (bLinkActivated)
	{
		FindAllOtherLinkComps();

		for (ULinkComponent* i : LinkComps)
		{
			//Check Obstacles.
			bool result = CheckEdgeCanExist(i);

			if (result)
			{
				TrySpawnEdge(i);
			}
			else
			{
				TryRemoveEdge(i);
			}
		}
	}
	else
	{
		TryRemoveAllEdges();
	}
}

void ULinkComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 기획 단계에서 overlap Begin되면 감지할 ULinkComponent 를 추가하려고 했는데
	// 어차피 Timer로 주기적으로 감지하게 되어 BeginOverlap에서 아무 것도 안함
	// 혹시 필요할 일이 있을지도 모르니 냅둠.
}

void ULinkComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//다른 LinkComponent가 Overlap이 끝날 때 Edge를 제거하는 작업.

	if (IsValid(OtherActor))
	{
		ULinkComponent* linkComp = OtherActor->FindComponentByClass<ULinkComponent>();

		if (IsValid(linkComp))
		{
			TryRemoveEdge(linkComp);
		}
	}
}

