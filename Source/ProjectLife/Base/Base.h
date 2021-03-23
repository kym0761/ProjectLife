// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Base.Generated.h"
/**
 * 
 */
 //Interactive Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

//Actual Interactive Interface Class. You must Use This When you Inherit Interface.
class IInteractive
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Interactive")
		void Interact(APawn* InteractCauser);

};

