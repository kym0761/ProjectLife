// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsHoldBase.h"
#include "LinkHoldBase.generated.h"

class ULinkComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ALinkHoldBase : public APhysicsHoldBase
{
	GENERATED_BODY()

public:

	ALinkHoldBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		ULinkComponent* LinkComponent;

};
