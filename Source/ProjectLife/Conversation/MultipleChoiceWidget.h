// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultipleChoiceWidget.generated.h"

class UVerticalBox;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UMultipleChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* VerticalBox_Choices;


};
