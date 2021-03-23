// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeechWidgetComponent.h"
#include "../UI/SpeechBubbleBase.h"
USpeechWidgetComponent::USpeechWidgetComponent()
{
	//Don't false in WidgetComponent. or it won't do Working.
	PrimaryComponentTick.bCanEverTick = true;

	SetWidgetSpace(EWidgetSpace::Screen);
	SetVisibility(false);
	SetHiddenInGame(true);

}

void USpeechWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	USpeechBubbleBase* bubbleRef = Cast<USpeechBubbleBase>(GetUserWidgetObject());
	if (bubbleRef)
	{
		bubbleRef->OnSpeechEnd.AddDynamic(this, &USpeechWidgetComponent::SpeechEnd);
		bubbleRef->SetNameText(GetOwner()->GetName());
	}
}

void USpeechWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpeechWidgetComponent::SpeechTrigger(FString InString)
{
	USpeechBubbleBase* bubbleRef = Cast<USpeechBubbleBase>(GetUserWidgetObject());

	if(bubbleRef)
	{
		SetVisibility(true);
		SetHiddenInGame(false);
		bubbleRef->StartSpeech(InString);
	}
}

void USpeechWidgetComponent::SpeechEnd()
{
	SetVisibility(false);
	SetHiddenInGame(true);
}
