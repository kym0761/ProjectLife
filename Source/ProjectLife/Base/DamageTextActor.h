// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTextActor.generated.h"

class UWidgetComponent;
class UDamageTextWidget;
class UProjectileMovementComponent;
UCLASS()
class PROJECTLIFE_API ADamageTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageTextActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
		UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<UDamageTextWidget> DamageTextClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
		float AppliedDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
		UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
