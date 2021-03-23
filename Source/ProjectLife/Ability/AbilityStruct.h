// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityStruct.Generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	None UMETA(DisplayName = "None"),
	Heal UMETA(DisplayName = "Heal"),
	StatUp UMETA(DisplayName = "StatUp"),
	
};

UENUM(BlueprintType)
enum class EDeBuffType : uint8
{
	None UMETA(DisplayName = "None"),
	Poison UMETA(DisplayName = "Poison"),
	StatDown UMETA(DisplayName = "StatDown"),

};

USTRUCT(BlueprintType)
struct FBuffDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		float BuffDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		float BuffAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		EBuffType BuffType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		float CastingTime;

	FBuffDataStruct();

};

USTRUCT(BlueprintType)
struct FDeBuffDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
		float DeBuffDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
		float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
		float DeBuffAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
		EDeBuffType DeBuffType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		float CastingTime;

	FDeBuffDataStruct();

};