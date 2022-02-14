// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChoiceSlot.generated.h"


class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UChoiceSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* TextBlock_ChoiceText;

	UPROPERTY(Meta = (BindWidget))
		UImage* Image_ChoiceIcon;

	//UPROPERTY(Meta = (BindWidget))
	//	UImage* Image_Background;

};
