// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTorchBase.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

AFireTorchBase::AFireTorchBase()
{
	FireOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("FireOverlap"));
	FireOverlap->InitBoxExtent(FVector(64.0f,64.0f,64.0f));
	FireOverlap->SetupAttachment(RootComponent);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(RootComponent);
	FireEffect->bAutoActivate = false;

	bFireOn = false;
}

void AFireTorchBase::FireOn()
{
	FireEffect->Activate();
	bFireOn = true;
}

void AFireTorchBase::FireOff()
{
	FireEffect->DeactivateImmediate();
	bFireOn = false;
}

void AFireTorchBase::Combust_Implementation()
{
	FireOn();
}

void AFireTorchBase::NotifyActorBeginOverlap(AActor* OtherActor)
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
