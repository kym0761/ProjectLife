// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTorch.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

AFireTorch::AFireTorch()
{
	FireOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("FireOverlap"));
	FireOverlap->InitBoxExtent(FVector(64.0f,64.0f,64.0f));
	FireOverlap->SetupAttachment(RootComponent);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(RootComponent);
	FireEffect->bAutoActivate = false;

	bFireOn = false;
}

void AFireTorch::FireOn()
{
	FireEffect->Activate();
	bFireOn = true;


	if (!CombustTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireTorch::OverlapCombust, 0.1f, true, 0.0f);
	}
}

void AFireTorch::FireOff()
{
	FireEffect->DeactivateImmediate();
	bFireOn = false;

	if (CombustTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}
}

void AFireTorch::Combust_Implementation()
{
	FireOn();
}

//void AFireTorch::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	if (bFireOn)
//	{
//		bool bInterfaceValid = OtherActor->GetClass()->ImplementsInterface(UCombustible::StaticClass());
//
//		if (bInterfaceValid)
//		{
//			ICombustible::Execute_Combust(OtherActor);
//		}
//	}
//
//
//}

void AFireTorch::OverlapCombust()
{
	if (bFireOn)
	{
		TArray<AActor*> overlapActors;

		FireOverlap->GetOverlappingActors(overlapActors);
		overlapActors.Remove(this);

		for (AActor* i : overlapActors)
		{
			bool bInterfaceValid = i->GetClass()->ImplementsInterface(UCombustible::StaticClass());
			if (bInterfaceValid)
			{
				ICombustible::Execute_Combust(i);
			}
		}
	}

}
