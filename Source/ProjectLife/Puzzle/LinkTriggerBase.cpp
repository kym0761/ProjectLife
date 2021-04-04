// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkTriggerBase.h"
#include "LinkComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleInterfaces.h"

ALinkTriggerBase::ALinkTriggerBase()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	LinkComponent = CreateDefaultSubobject<ULinkComponent>(TEXT("LinkComponent"));
	LinkComponent->SetupAttachment(RootComponent);
}

void ALinkTriggerBase::SetTriggerActivate(bool InVal)
{
	bTriggerActive = InVal;
	Trigger();
}

void ALinkTriggerBase::Trigger()
{
	for (AActor* i : TriggeringArray)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UTriggerable::StaticClass());
		if (bInterfaceValid)
		{
			ITriggerable::Execute_TriggerAction(i);
		}
	}
}
