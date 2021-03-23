// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Buff.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ABuff : public AAbility
{
	GENERATED_BODY()
public:
	ABuff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
		FBuffDataStruct BuffData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff")
		float CurrentDurationTime;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayBuff();
		void PlayBuff_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent)
		void EndBuff();
		void EndBuff_Implementation();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
