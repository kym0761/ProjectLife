// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicWeapon.h"
#include "MeleeWeapon.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AMeleeWeapon : public ABasicWeapon
{
	GENERATED_BODY()

public:

	AMeleeWeapon();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* AttackCollision;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OverlapAttackCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void AttackStart() override;
	virtual void AttackEnd() override;

};
