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
}

void AFireTorch::FireOff()
{
	FireEffect->DeactivateImmediate();
	bFireOn = false;
}

void AFireTorch::Combust_Implementation()
{
	FireOn();
}

void AFireTorch::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bFireOn)
	{
		bool bInterfaceValid = OtherActor->GetClass()->ImplementsInterface(UCombustible::StaticClass());

		if (bInterfaceValid)
		{
			ICombustible::Execute_Combust(OtherActor);
		}
	}


}
