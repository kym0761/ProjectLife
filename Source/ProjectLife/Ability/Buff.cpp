// Fill out your copyright notice in the Description page of Project Settings.


#include "Buff.h"
#include "../Base/BasicPlayerController.h"
ABuff::ABuff()
{

}

void ABuff::BeginPlay()
{
	Super::BeginPlay();

	CurrentDurationTime = BuffData.BuffDuration;

	PlayBuff();

	if (GetOwner())
	{
		ABasicPlayerController* playerController = Cast<APawn>(GetOwner())->GetController<ABasicPlayerController>();
		if (playerController)
		{
			//call to Add BuffIcon to ConditionUI.
			playerController->AddConditionIcon(this);
		}
	}

}

void ABuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDurationTime -= DeltaTime;

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-2, 5.0f, FColor::Magenta, FString("Buff Current : ")+FString::SanitizeFloat(CurrentDurationTime));
	//}

	if (CurrentDurationTime <= 0)
	{
		Destroy();
	}
}

void ABuff::PlayBuff_Implementation()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-2, 5.0f, FColor::Magenta, TEXT("Play Buff.. Please Override it."));
	}

}

void ABuff::EndBuff_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-2, 5.0f, FColor::Magenta, TEXT("End Buff.. Please Override it."));
	}
}

void ABuff::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EndBuff();

	if (GetOwner())
	{
		ABasicPlayerController* playerController = Cast<APawn>(GetOwner())->GetController<ABasicPlayerController>();
		if (playerController)
		{
			//call to Add BuffIcon to ConditionUI.
			playerController->RemoveConditionIcon(this);
		}
	}
}
