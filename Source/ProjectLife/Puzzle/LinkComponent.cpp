// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkComponent.h"
#include "LinkEdgeBase.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LinkHoldBase.h"
#include "LinkTriggerBase.h"
#include "PuzzleTriggerBase.h"


// Sets default values for this component's properties
ULinkComponent::ULinkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bRootLink = false;
	bLinkActivated = false;

	//InitSphereRadius(500.0f);
	MaxDistance = 500.0f;
}


// Called when the game starts
void ULinkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//If RootLink, Set Activate.
	if (bRootLink)
	{
		bLinkActivated = true;
		ALinkTriggerBase* owner = Cast<ALinkTriggerBase>(GetOwner());
		if (IsValid(owner))
		{
			owner->bTriggerActive = bLinkActivated;
		}
	}

	FindAllOtherLinkComps();

}


// Called every frame
void ULinkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	LinkJob();
}

bool ULinkComponent::GetLinkActivate() const
{
	return bLinkActivated;
}

void ULinkComponent::SetLinkActivate(bool InVal)
{
	//It Not RootLink, Activated Can be Variable.
	if (!bRootLink)
	{
		bLinkActivated = InVal;

		ALinkTriggerBase* owner= Cast<ALinkTriggerBase>(GetOwner());
		if (IsValid(owner))
		{
			owner->SetTriggerActivate(bLinkActivated);
		}

	}
}

bool ULinkComponent::CheckLinkedWithRoot()
{
	bool result = false;

	//Array for Traversing
	TArray<ULinkComponent*> ElectricComp;
	
	//Cache for Already Traversing.
	TArray<ULinkComponent*> ElectricCompRemember;
	TArray<ALinkEdgeBase*> ElectricEdgeRemember;

	//first, Add Self.
	ElectricComp.Add(this);
	ElectricCompRemember.AddUnique(this);

	while (ElectricComp.Num() > 0)
	{

		ULinkComponent* popResult = ElectricComp.Pop();

		if (IsValid(popResult))
		{
			for (ALinkEdgeBase* i : popResult->LinkEdges)
			{

				//find Edge Currently Not Traversed.
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

	//Check there is a RootLink In traversed Components.
	for (ULinkComponent* i : ElectricCompRemember)
	{
		if (i->bRootLink)
		{
			result = true;
			break;
		}
	}

	return result;

}

bool ULinkComponent::CheckEdgeCanExist(ULinkComponent* OtherLinkComp)
{
	
	if (!IsValid(this) && !IsValid(OtherLinkComp))
	{
		UE_LOG(LogTemp, Warning, TEXT("Link Component Not Valid"));
		return false;
	}

	//Check One of them is Active.
	if (GetLinkActivate() || OtherLinkComp->GetLinkActivate())
	{
		TArray<AActor*> ignores;

		TArray<AActor*> arr1;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALinkTriggerBase::StaticClass(), arr1);
		TArray<AActor*> arr2;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALinkHoldBase::StaticClass(), arr2);

		ignores.Append(arr1);
		ignores.Append(arr2);

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
			hit,
			true
		);

		//If There is Any Collision, Edge Can Exist.
		if (result == false)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s is Success.  ----- Other : %s"), *GetOwner()->GetName(), *OtherLinkComp->GetOwner()->GetName());
			return true;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Failed."));
	return false;

}

bool ULinkComponent::CheckCompDistance(ULinkComponent* OtherLinkComp)
{
	float distance = UKismetMathLibrary::Vector_Distance(GetComponentLocation(), OtherLinkComp->GetComponentLocation());

	if (distance <= MaxDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void ULinkComponent::TrySpawnEdge(ULinkComponent* OtherLinkComp)
{
	bool bConnectionExist = false;

	if (!IsValid(OtherLinkComp))
	{
		//if (GEngine)
		//{
		//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Yellow, TEXT("Other Not Valid"));
		//}
		return;
	}

	if (!CheckLinkedWithRoot())
	{
		//UE_LOG(LogTemp, Warning, TEXT(" Not Root Linked ====>current %s / OtherComp : %s"), *GetOwner()->GetName(), *OtherLinkComp->GetOwner()->GetName());
		return;
	}

	//check LinkEdge that emplace "OtherLinkComp" already Exist.
	for (ALinkEdgeBase* i : LinkEdges)
	{
		bool temp = i->LinkComps.Find(OtherLinkComp) != -1 ? true : false;
		if (temp)
		{
			bConnectionExist = true;
		}
	}

	//there is not connection, Spawn Edge.
	if (!bConnectionExist)
	{
		if (LinkEdgeClass)
		{
			ALinkEdgeBase* edge = GetWorld()->SpawnActorDeferred<ALinkEdgeBase>(LinkEdgeClass, GetComponentTransform(),nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (edge)
			{
				edge->InitializeCompRefs(this,OtherLinkComp);
				edge->FinishSpawning(GetComponentTransform());
				LinkEdges.Add(edge);
				
				OtherLinkComp->LinkEdges.Add(edge);
				OtherLinkComp->SetLinkActivate(true);

				AdjacentLinkComps.Add(OtherLinkComp);
				OtherLinkComp->AdjacentLinkComps.Add(this);

				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Yellow, TEXT("Edge Spawn success"));
				}

			}
			//else
			//{
			//	if (GEngine)
			//	{
			//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Yellow, TEXT("Unknown2"));
			//	}
			//}
		}
		//else
		//{
		//	if (GEngine)
		//	{
		//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Yellow, TEXT("Unknown1"));
		//	}
		//}
	}
	//else
	//{
	//	if (GEngine)
	//	{
	//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Yellow, TEXT("Unknown"));
	//	}
	//}

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

	//if not Find, End Function.
	if (index1 == -1 && index2 == -1)
	{
		return;
	}

	//get Ref of Edge that want to remove
	ALinkEdgeBase* edgeToRemove = LinkEdges[index1];

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
	//find Other Link Components Except "this"

	TArray<AActor*> actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), actors);

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
		SetLinkActivate(result);
		TryRemoveAllEdges();
	}
}

void ULinkComponent::LinkJob()
{
	if (bLinkActivated)
	{
		for (ULinkComponent* i : LinkComps)
		{
			bool result1 = CheckCompDistance(i);
			bool result2 = CheckEdgeCanExist(i);

			if (result1 && result2)
			{
				TrySpawnEdge(i);
			}
			else
			{
				TryRemoveEdge(i);
			}
		}
	}
}

