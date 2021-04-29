// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Cow.generated.h"

class UMilkComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ACow : public AAnimal
{
	GENERATED_BODY()
	
public:

	ACow();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UMilkComponent* MilkComponent;


};
