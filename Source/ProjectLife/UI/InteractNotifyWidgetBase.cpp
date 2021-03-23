// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractNotifyWidgetBase.h"
#include "Components/TextBlock.h"

void UInteractNotifyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInteractNotifyWidgetBase::NotifyInteract(AActor* InActor)
{
	SetVisibility(ESlateVisibility::Visible);

	if (NameTextBlock)
	{
		if (InActor)
		{
			NameTextBlock->SetText(FText::FromString(InActor->GetName()));
		}
	}
}

void UInteractNotifyWidgetBase::UnnotifyInteract()
{
	SetVisibility(ESlateVisibility::Hidden);
	if (NameTextBlock)
	{
		//Set Default.
		NameTextBlock->SetText(FText::FromString(FString("Who?")));
	}
}
