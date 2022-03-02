// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ConversationStruct.Generated.h"

/**
 *  ConversationData struct
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
struct FConversationData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int32 ConversationID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ConversationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConversationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionType Emotion;

	FConversationData();

};

USTRUCT(BlueprintType)
struct FConversationChoiceData : public FTableRowBase
{
	GENERATED_BODY()

public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int32 ConversationID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ChoiceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionType Emotion;

	FConversationChoiceData();

};