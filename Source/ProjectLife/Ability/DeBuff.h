// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "DeBuff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ADeBuff : public AAbility
{
	GENERATED_BODY()

public:
	ADeBuff();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeBuff")
	//	FDeBuffDataStruct DeBuffData;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintImplementableEvent)
	//	void PlayDeBuff();
	//	void PlayDeBuff_Implementation();

	//UFUNCTION(BlueprintImplementableEvent)
	//	void EndDeBuff();
	//	void EndDeBuff_Implementation();


	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
