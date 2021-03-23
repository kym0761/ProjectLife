// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechBubbleBase.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "TimerManager.h"
#include "../Base/BasicCharacter.h"
#include "Components/WidgetComponent.h"
void USpeechBubbleBase::NativeConstruct()
{
	CurrentLength = 0;
}

void USpeechBubbleBase::StartSpeech(FString InSpeech)
{
	CurrentLength = 0;
	
	if (SpeechTextBlock)
	{
		SpeechTextBlock->SetText(FText::GetEmpty());
	}

	SpeechString = InSpeech;
	float timeRate = 1.0f / SpeechSpeed;
	GetWorld()->GetTimerManager().SetTimer(SpeechTimer, this, &USpeechBubbleBase::Speech, timeRate, true);
	

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Start Speech OK"));
		FString temp = FString("Current rate : ") + FString::SanitizeFloat(timeRate);
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, temp);
	}*/
}

void USpeechBubbleBase::Speech()
{
	FString temp = UKismetStringLibrary::GetSubstring(SpeechString, 0, CurrentLength);
	SpeechTextBlock->SetText(FText::FromString(temp));

	if (CurrentLength < SpeechString.Len())
	{
		CurrentLength++;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpeechEndTimer, this, &USpeechBubbleBase::EndSpeech, 1.0f, false, EndTime);
		GetWorld()->GetTimerManager().ClearTimer(SpeechTimer);
	}

	//if (GEngine)
	//{
	//	FString intTemp = FString("Current Length : ")+FString::FromInt(CurrentLength);
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Cyan, intTemp);
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Speech OK"));
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Blue, temp);
	//}

}

void USpeechBubbleBase::EndSpeech()
{
	OnSpeechEnd.Broadcast();

	GetWorld()->GetTimerManager().ClearTimer(SpeechEndTimer);

}

void USpeechBubbleBase::SetNameText(FString InName)
{
	if (NameTextBlock)
	{
		NameTextBlock->SetText(FText::FromString(InName));
	}
}
