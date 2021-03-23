// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidgetBase.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UDamageTextWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* DamageTextBlock;

	virtual void NativeConstruct() override;

	void SetDamageText(float InDamage);

};
