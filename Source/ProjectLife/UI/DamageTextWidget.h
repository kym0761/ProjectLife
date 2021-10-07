// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* DamageTextBlock;

	virtual void NativeConstruct() override;

	void SetDamageText(float InDamage);

};
