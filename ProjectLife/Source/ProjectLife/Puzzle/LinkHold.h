// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsHold.h"
#include "LinkHold.generated.h"

class ULinkComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ALinkHold : public APhysicsHold
{
	GENERATED_BODY()

public:

	ALinkHold();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<ULinkComponent> LinkComponent;

};
