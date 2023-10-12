// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float MaxStamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 100000.0f))
		float HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 100000.0f))
		float Shield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float BaseAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float AdditionalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float AttackCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float BaseDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float AdditionalDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float DefenseCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float CritcalHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat", Meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float AdditionalCriticalHit;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void DealDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Heal")
		void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Heal")
		void RefillStamina(float RefillAmount);
		

	void ClearAdditionalStat();
	void ClearStatCoefficient();

	void ApplyAdditionalStat(FEquipmentItemData InData);
	//void ApplyStatCoefficient();
};
