// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityStruct.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS()
class PROJECTLIFE_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FAbilityDataStruct AbilityData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
		float CurrentDurationTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
		AActor* AbilityOwner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
		AActor* AbilityTarget;

	FTimerHandle AbilityCountdownTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetAbilityOwner(AActor* Value);

	//temporally Can Call In Blueprint.
	UFUNCTION(BlueprintCallable)
	void BeginAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateAbility();
	virtual void ActivateAbility_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void EndAbility();
	virtual void EndAbility_Implementation();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void AbilityTimerFunction();
};
