// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/InteractiveInterface.h"
#include "GameFramework/Character.h"
#include "Animal.generated.h"

UCLASS()
class PROJECTLIFE_API AAnimal : public ACharacter, public IInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<TObjectPtr<USoundBase>> InteractSound;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
		bool bInteractOK;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact_Implementation(APawn* InteractCauser);

	UFUNCTION()
	void WhenSoundFinished();

	void PlayInteractSound();
};
