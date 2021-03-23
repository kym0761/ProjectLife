// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTriggerBase.generated.h"

UCLASS()
class PROJECTLIFE_API APuzzleTriggerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTriggerBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
		bool bTriggerActive;

	//who will Trigger this? this Will be Initialized when Beginplay() played!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
		TArray<APuzzleTriggerBase*> TriggerArray;

	//which you Want to Trigger? Add it from in the World.  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		TArray<AActor*> TriggeringArray;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeTriggerArray();
};
