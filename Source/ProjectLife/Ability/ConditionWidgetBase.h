// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConditionWidgetBase.generated.h"

class UHorizontalBox;
//class UBuffIconWidgetBase;
class UConditionIconBase;
class AAbility;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConditionWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
		UHorizontalBox* ConditionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UConditionIconBase> ConditionIconClass;

	virtual void NativeConstruct() override;

	void AddIcon(AAbility* ConditionActorRef);
	void RemoveIcon(AAbility* ConditionActorRef);
};
