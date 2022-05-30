// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsHold.h"
#include "FireTorch.generated.h"

class UNiagaraComponent;

/**
 *  전체적인 로직은 AFireStand와 유사함. APhysicsHold를 상속받았기 때문에 AFireStand를 상속받지 못하여 따로 구현.
 */
UCLASS()
class PROJECTLIFE_API AFireTorch : public APhysicsHold, public ICombustible
{
	GENERATED_BODY()
	
public:

	AFireTorch();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		UBoxComponent* FireOverlap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		UNiagaraComponent* FireEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		bool bFireOn;

	void FireOn();

	void FireOff();

	virtual void Combust_Implementation();

	////TODO : FireTorch Function Will Remake Like FireStand.
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle CombustTimer;
	UFUNCTION()
		void OverlapCombust();
};
