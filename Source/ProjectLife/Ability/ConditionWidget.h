// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConditionWidget.generated.h"

class UHorizontalBox;
class UConditionIconWidget;
class AAbility;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConditionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		UHorizontalBox* ConditionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UConditionIconWidget> ConditionIconClass;

	virtual void NativeConstruct() override;

	void AddIcon(AAbility* ConditionActorRef);
	void RemoveIcon(AAbility* ConditionActorRef);
};
