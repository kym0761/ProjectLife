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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	//	FBuffDataStruct BuffData;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
