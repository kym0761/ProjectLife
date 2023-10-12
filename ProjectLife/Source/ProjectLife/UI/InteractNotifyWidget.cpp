// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractNotifyWidget.h"
#include "Components/TextBlock.h"

void UInteractNotifyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ObjectRef = nullptr;
}

void UInteractNotifyWidget::NotifyInteract(UObject* InObject)
{
	// If it Can be Visible && Identical Actor Selected, Don't Do Anything.
	if (GetVisibility() == ESlateVisibility::Visible && ObjectRef == InObject)
	{
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
	if (IsValid(NameTextBlock))
	{
		if (IsValid(InObject))
		{
			NameTextBlock->SetText(FText::FromString(InObject->GetName()));
			ObjectRef = InObject;
		}
	}
}

void UInteractNotifyWidget::UnnotifyInteract()
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
		ObjectRef = nullptr;
	}
}
