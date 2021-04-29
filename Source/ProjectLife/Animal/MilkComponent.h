// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LivestockComponent.h"
#include "MilkComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UMilkComponent : public ULivestockComponent
{
	GENERATED_BODY()
	
public:

	UMilkComponent();

	void MakeMilk();

};
