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

	//temp to set owner in blueprint test
	UFUNCTION(BlueprintCallable)
	void SetAbilityOwner(AActor* Value);

	UFUNCTION(BlueprintCallable)
	void StartAbility();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateActiveEffect();
	virtual void ActivateActiveEffect_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void ActivatePassiveEffect();
	virtual void ActivatePassiveEffect_Implementation();

	//It may be call when Ability Actor Destroyed.
	UFUNCTION(BlueprintNativeEvent)
	void EndAbility();
	virtual void EndAbility_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateEndEffect();
	virtual void ActivateEndEffect_Implementation();

	//It May be Called when Dispelled or Ability Ended Un-Favorably.
	UFUNCTION(BlueprintCallable)
	void DestroyAbilityWithNoEndEffect();
	
	//it May be Called when Ability Ended Successfully.
	UFUNCTION(BlueprintCallable)
	void DestroyAbilityWithEndEffect();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void AbilityEndTimerFunction();
};
