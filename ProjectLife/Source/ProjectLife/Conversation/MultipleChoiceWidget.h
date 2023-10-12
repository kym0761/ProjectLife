// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultipleChoiceWidget.generated.h"

class UVerticalBox;

/**
 *  !! May Not Need.
 */
UCLASS()
class PROJECTLIFE_API UMultipleChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UVerticalBox> VerticalBox_Choices;


};
