// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTriggerBase.h"
#include "LinkTriggerBase.generated.h"

class ULinkComponent;
class UStaticMeshComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ALinkTriggerBase : public APuzzleTriggerBase
{
	GENERATED_BODY()

public:

	ALinkTriggerBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		ULinkComponent* LinkComponent;
	
	void SetTriggerActivate(bool InVal);


	virtual void Trigger();
};
