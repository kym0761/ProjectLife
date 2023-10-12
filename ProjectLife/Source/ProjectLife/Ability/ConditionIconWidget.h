// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConditionIconWidget.generated.h"

class UImage;
class AAbility;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConditionIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		TObjectPtr<UImage> ConditionImage;

private:

	//Buff or DeBuff
	UPROPERTY()
		TObjectPtr<AAbility> ConditionRef;

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void InitIcon(AAbility* ConditionActorRef);

	AAbility* GetConditionRef() const;

};
