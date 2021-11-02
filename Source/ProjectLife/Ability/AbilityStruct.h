// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityStruct.Generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None UMETA(DisplayName = "None"),
	Heal UMETA(DisplayName = "Heal"),
	StatUp UMETA(DisplayName = "StatUp"),
	Poison UMETA(DisplayName = "Poison"),
	StatDown UMETA(DisplayName = "StatDown"),

};

USTRUCT(BlueprintType)
struct FAbilityDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		float AbilityEffectAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		EAbilityType AbilityType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		bool bIsInifinity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		float CastingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		UTexture2D* Thumbnail;



	FAbilityDataStruct();

};