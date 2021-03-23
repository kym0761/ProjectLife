// Fill out your copyright notice in the Description page of Project Settings.


#include "DeBuff.h"
#include "../Base/BasicPlayerController.h"

ADeBuff::ADeBuff()
{

}

void ADeBuff::BeginPlay()
{
	Super::BeginPlay();

	CurrentDurationTime = DeBuffData.DeBuffDuration;

	PlayDeBuff();

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

void ADeBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentDurationTime -= DeltaTime;

	if (CurrentDurationTime <= 0)
	{
		Destroy();
	}

}

void ADeBuff::PlayDeBuff_Implementation()
{
}

void ADeBuff::EndDeBuff_Implementation()
{
}

void ADeBuff::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetOwner())
	{
		ABasicPlayerController* playerController = Cast<APawn>(GetOwner())->GetController<ABasicPlayerController>();
		if (playerController)
		{
			//call to Add BuffIcon to ConditionUI.
			playerController->RemoveConditionIcon(this);
		}
	}

	EndDeBuff();
}