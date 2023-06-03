// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FarmingTool.h"
#include "Milker.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AMilker : public AFarmingTool
{
	GENERATED_BODY()

public:

	AMilker();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Component")
		TObjectPtr<USphereComponent> Sphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Milking();
};
