// Fill out your copyright notice in the Description page of Project Settings.


#include "Milker.h"
#include "Components/SphereComponent.h"
#include "../Animal/Cow.h"
#include "../Animal/LivestockProduceComponent.h"
#include "../Item/Item.h"
AMilker::AMilker()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->InitSphereRadius(48.0f);
}

void AMilker::BeginPlay()
{
	Super::BeginPlay();

}

void AMilker::Milking()
{
	if (IsValid(Sphere))
	{
		TArray<AActor*> cows;

		Sphere->GetOverlappingActors(cows,ACow::StaticClass());

		//Sort by Distance. descending order
		cows.Sort(
			[this](const AActor& a, const AActor& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetActorLocation())
					< FVector::Distance(GetActorLocation(), b.GetActorLocation());
			}
		);


		//UE_LOG(LogTemp, Warning, TEXT("Current animal Number : %d"), animals.Num());

		AItem* produce = nullptr;
		for (AActor* i : cows)
		{
			ULivestockProduceComponent* produceComp = i->FindComponentByClass<ULivestockProduceComponent>();
			if (IsValid(produceComp))
			{
				produce = produceComp->Produce();
				break;
			}
		}

		if (IsValid(produce))
		{
			//TODO : Hold Produce to Milker's Owner. 
		}

	}
}
