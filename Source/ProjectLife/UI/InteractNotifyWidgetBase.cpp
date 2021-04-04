// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractNotifyWidgetBase.h"
#include "Components/TextBlock.h"

void UInteractNotifyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	ActorRef = nullptr;
}

void UInteractNotifyWidgetBase::NotifyInteract(AActor* InActor)
{
	// If it Can be Visible && Identical Actor Selected, Don't Do Anything.
	if (GetVisibility() == ESlateVisibility::Visible && ActorRef == InActor)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
	if (IsValid(NameTextBlock))
	{
		if (InActor)
		{
			NameTextBlock->SetText(FText::FromString(InActor->GetName()));
			ActorRef = InActor;
		}
	}
}

void UInteractNotifyWidgetBase::UnnotifyInteract()
{
	//if Already Hidden, Don't Do Anything.
	if (GetVisibility() == ESlateVisibility::Hidden)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Hidden);
	if (IsValid(NameTextBlock))
	{
		//Set Default.
		NameTextBlock->SetText(FText::FromString(FString("Who?")));
		ActorRef = nullptr;
	}
}
