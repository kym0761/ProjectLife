// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkTrigger.h"
#include "LinkComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleInterfaces.h"

ALinkTrigger::ALinkTrigger()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	LinkComponent = CreateDefaultSubobject<ULinkComponent>(TEXT("LinkComponent"));
	LinkComponent->SetupAttachment(RootComponent);
}

void ALinkTrigger::SetTriggerActivate(bool InVal)
{
	bTriggerActive = InVal;
	Trigger();
}

void ALinkTrigger::Trigger()
{
	for (AActor* i : ToTrigger)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UTriggerable::StaticClass());
		if (bInterfaceValid)
		{
			ITriggerable::Execute_TriggerAction(i);
		}
	}
}
