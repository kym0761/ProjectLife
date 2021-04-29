// Fill out your copyright notice in the Description page of Project Settings.


#include "MilkComponent.h"

UMilkComponent::UMilkComponent()
{
}

void UMilkComponent::MakeMilk()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.0f,FColor::Black,TEXT("Milk Made!"));
	}

}
