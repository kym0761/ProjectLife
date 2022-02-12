// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechBubbleWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/WidgetComponent.h"
void USpeechBubbleWidget::NativeConstruct()
{
	CurrentLength = 0;
}

void USpeechBubbleWidget::StartSpeech(FString InSpeech)
{
	CurrentLength = 0;
	
	if (SpeechTextBlock)
	{
		SpeechTextBlock->SetText(FText::GetEmpty());
	}

	SpeechString = InSpeech;
	float timeRate = 1.0f / SpeechSpeed;
	GetWorld()->GetTimerManager().SetTimer(SpeechTimer, this, &USpeechBubbleWidget::Speech, timeRate, true);
	
}

void USpeechBubbleWidget::Speech()
{
	FString temp = UKismetStringLibrary::GetSubstring(SpeechString, 0, CurrentLength);
	SpeechTextBlock->SetText(FText::FromString(temp));

	if (CurrentLength < SpeechString.Len())
	{
		CurrentLength++;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpeechEndTimer, this, &USpeechBubbleWidget::EndSpeech, 1.0f, false, EndTime);
		GetWorld()->GetTimerManager().ClearTimer(SpeechTimer);
	}

}

void USpeechBubbleWidget::EndSpeech()
{
	OnSpeechEnd.Broadcast();

	GetWorld()->GetTimerManager().ClearTimer(SpeechEndTimer);

}

void USpeechBubbleWidget::SetNameText(FString InName)
{
	if (NameTextBlock)
	{
		NameTextBlock->SetText(FText::FromString(InName));
	}
}
