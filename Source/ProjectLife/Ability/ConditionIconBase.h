// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConditionIconBase.generated.h"

class UImage;
class AAbility;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConditionIconBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UImage* ConditionImage;

	//Buff or DeBuff
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		AAbility* ConditionRef;

	virtual void NativeConstruct() override;

	void InitIcon(AAbility* ConditionActorRef);
};
