// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animal.h"
#include "Chicken.generated.h"

class ULivestockProduceComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AChicken : public AAnimal
{
	GENERATED_BODY()
	
public:

	AChicken();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<ULivestockProduceComponent> LivestockProduceComponent;

};
