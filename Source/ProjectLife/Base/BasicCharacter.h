// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
//class UInventoryComponent;
class UStatComponent;
class UEquipmentComponent;
class ABasicWeapon;
class USpeechWidgetComponent;
class ADamageTextActor;
class USceneComponent;
class UAbilityComponent;

//class AFarmingTool;
UENUM(BlueprintType)
enum class ECameraType : uint8
{
	TopView UMETA(DisplayName = "TopView"),
	ThirdPersonView UMETA(DisplayName = "ThirdPersonView")
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	None UMETA(DisplayName = "None"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy")
};

UCLASS()
class PROJECTLIFE_API ABasicCharacter : public ACharacter, public IInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UCameraComponent* Camera;

	////Inventory Component;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//	UInventoryComponent* Inventory;

	//StatComponent.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UStatComponent* StatComponent;

	//EquipmentComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UEquipmentComponent* EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABasicWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		ABasicWeapon* CurrentWeapon;

	//Current CameraView Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
		ECameraType CameraType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Speech")
		USpeechWidgetComponent* SpeechBubbleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		TSubclassOf<ADamageTextActor> DamageTextActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hold")
		USceneComponent* HoldPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hold")
		bool bHoldSomething;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hold")
		AActor* CurrentHold;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Farming")
	//	AFarmingTool* FarmingTool;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	//Camera Functions
	void RotateTopView();
	void RotateTopView_Reverse();
	void ChangeCameraType();
	void SettingWithCameraType();

	const float InteractCheckInterval = 0.1f;
	FTimerHandle InteractCheckTimer;
	//Check There is Interactable Actor.
	void InteractCheck();

	//Call Interact Function which has Interactive Interface. 
	void InteractTrigger();

	//Interactee Means Someone or Something is interacted by Interact() Function. Concept is Something like [employ"ee"]
	//UFUNCTION needed temporally for using in blueprint.
	UFUNCTION(BlueprintCallable)
	UObject* FindInteractee();

	void ToggleInventory();

	UFUNCTION(BlueprintCallable) //Temporary In Blueprint Cause by Farming tool
	void Hold(AActor* ToHold);
	void UnHold();

	//virtual void Interact(APawn* InteractCauser);
	void Interact_Implementation(APawn* InteractCauser);
};
