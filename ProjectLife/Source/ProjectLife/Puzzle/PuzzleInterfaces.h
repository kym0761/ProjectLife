// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleInterfaces.generated.h"

/*
ITriggerable : 트리거 대상일 때 필요한 인터페이스
IResetable : 리셋이 가능한 대상일 때 필요한 인터페이스. ex) ResetButtonTrigger
ICombustible : 불 붙는게 가능한 대상일 때 필요한 인터페이스. ex)FireTorch, FireStand
*/

 //Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UTriggerable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class ITriggerable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Trigger")
		void TriggerAction();

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UResetable : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class IResetable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "reset")
		void Reset();

};

//Interface Class Base. Don't Use.
UINTERFACE(Blueprintable)
class UCombustible : public UInterface
{
	GENERATED_BODY()
};

//Actual Interface Class. You must Use This When you Inherit Interface.
class ICombustible
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Combust")
		void Combust();

};