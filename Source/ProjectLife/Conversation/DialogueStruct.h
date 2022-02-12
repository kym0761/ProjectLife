// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueStruct.Generated.h"

/**
 *  DialogueInfo struct
 */
UENUM(BlueprintType)
enum class EEmotionType : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Happy UMETA(DisplayName = "Happy"),
	Sad UMETA(DisplayName = "Sad"),
	Angry UMETA(DisplayName = "Angry"),
	Embarrassed UMETA(DisplayName = "Embarrassed"),
	Impressed UMETA(DisplayName = "Impressed")
};

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DialogueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionType Emotion;

	FDialogueData();

};