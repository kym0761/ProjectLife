// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
//#include "GameFramework/DamageType.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "AttackStruct.Generated.h"

UENUM(BlueprintType)
enum class EGameAttackType : uint8
{
	None UMETA(DisplayName = "None"),
	Point UMETA(DisplayName = "Point"),
	Radial UMETA(DisplayName = "Radial"),
};

UENUM(BlueprintType)
enum class EGameAttackRangeType : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Range UMETA(DisplayName = "Range"),
};

UENUM(BlueprintType)
enum class EGameDamageType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical UMETA(DisplayName = "Physical"),
	Magical UMETA(DisplayName = "Magical")
};

//EGameDefenseType
UENUM(BlueprintType)
enum class EGameDefenseType : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Heavy UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class EGameElementType : uint8
{
	None UMETA(DisplayName = "None"),
	Fire UMETA(DisplayName = "Fire"),
	Water UMETA(DisplayName = "Water"),
	Grass UMETA(DisplayName = "Grass"),
	Earth UMETA(DisplayName = "Earth"),
	Light UMETA(DisplayName = "Light"),
	Dark UMETA(DisplayName = "Dark")	
};


UCLASS(const,Blueprintable,BlueprintType)
class UCustomDamageType : public UDamageType
{
	GENERATED_BODY()
	//GENERATED_UCLASS_BODY()
//public:
//
//		UCustomDamageType();
//	
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageType")
//			EAttackType AttackType;
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageType")
//			EAttackRangeType AttackRangeType;
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageType")
//			EDamageType DamageType;

};

//USTRUCT(BlueprintType)
//struct FCustomPointDamageEvent : public FPointDamageEvent
//{
//	GENERATED_BODY()
//
//	UPROPERTY()
//		EAttackType AttackType;
//	UPROPERTY()
//		EDamageType DamageType;
//
//	FCustomPointDamageEvent() : FPointDamageEvent(), AttackType(EAttackType::None),DamageType(EDamageType::None) {}
//
//
//};
//
//USTRUCT(BlueprintType)
//struct FCustomRadialDamageEvent : public FRadialDamageEvent
//{
//	GENERATED_BODY()
//
//	UPROPERTY()
//		EAttackType AttackType;
//	UPROPERTY()
//		EDamageType DamageType;
//
//	FCustomRadialDamageEvent(): FRadialDamageEvent(), AttackType(EAttackType::None), DamageType(EDamageType::None) {}
//
//};