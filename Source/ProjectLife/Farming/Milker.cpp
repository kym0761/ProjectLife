// Fill out your copyright notice in the Description page of Project Settings.


#include "Milker.h"
#include "Components/SphereComponent.h"
#include "../Animal/Animal.h"
#include "../Animal/MilkComponent.h"
AMilker::AMilker()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
}

void AMilker::BeginPlay()
{
	Super::BeginPlay();

}

void AMilker::Milking()
{
	if (IsValid(Sphere))
	{
		TArray<AActor*> animals;

		Sphere->GetOverlappingActors(animals,AAnimal::StaticClass());

		//Sort by Distance. descending order
		animals.Sort(
			[this](const AActor& a, const AActor& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetActorLocation())
					< FVector::Distance(GetActorLocation(), b.GetActorLocation());
			}
		);


		//UE_LOG(LogTemp, Warning, TEXT("Current animal Number : %d"), animals.Num());

		for (AActor* i : animals)
		{
			UMilkComponent* milkComp = i->FindComponentByClass<UMilkComponent>();
			if (IsValid(milkComp))
			{
				//TODO : Make Milk
				milkComp->MakeMilk();
				break;
			}

		}



	}
}
