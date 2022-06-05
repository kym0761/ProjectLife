// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractDetectComponent.h"
#include "InteractiveInterface.h"

UInteractDetectComponent::UInteractDetectComponent()
{
	HasInteractive = nullptr;

}

void UInteractDetectComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractDetectComponent::OnSphereBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractDetectComponent::OnSphereEndOverlap);
 
}

void UInteractDetectComponent::CheckInteract()
{
	//현재 오버랩된 액터들을 전부 Get하고
	//오버랩된 액터 중에서 UInteractive 인터페이스를 가진 애들만 걸러내고
	//UInteractive를 가진 Actor들을 UInteractDetectComponent와 가장 가까운 순으로 정렬한 뒤
	//HasInteractive를 가장 가까운 Actor로 변경. 혹시 아무도 없다면 HasInteractive는 nullptr임.

	//Warning : 지금 오버랩된 상태에서 안에 있던 애들 위치가 바뀐다고 HasInteractive가 바뀌지 않음
	//적절한 주기로 CheckInteract를 하면 해결될 문제지만, 지금 딱히 고칠 필요 없을 듯.

	TArray<AActor*> overlapActors;
	TArray<AActor*> hasInteractives;

	GetOverlappingActors(overlapActors);
	//이 컴포넌트의 Owner는 제외
	overlapActors.Remove(GetOwner());

	for (AActor* i : overlapActors)
	{
		if (i->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			hasInteractives.Add(i);
		}
	}

	hasInteractives.Sort([this](const AActor& a, const AActor& b)
		{
			FVector compLocation = this->GetComponentLocation();

			float distA = FVector::Distance(compLocation, a.GetActorLocation());
			float distB = FVector::Distance(compLocation, b.GetActorLocation());

			return distA < distB;
		});

	if (hasInteractives.Num() > 0)
	{
		HasInteractive = hasInteractives[0];
	}
	else
	{
		HasInteractive = nullptr;
	}

}

void UInteractDetectComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Overlap Begin 할 때마다 한번씩 전체 오버랩을 한다.
	CheckInteract();

}

void UInteractDetectComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Overlap End 할 때마다 한번씩 전체 오버랩을 한다.
	CheckInteract();

}

AActor* UInteractDetectComponent::GetInteractiveActor() const
{
	//nullptr or Actor
	return HasInteractive;

}
