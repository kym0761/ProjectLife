// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
class AAbility;
class UMainHUD;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasicPlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UMainHUD> MainHUDClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
		UMainHUD* MainHUDRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
		class UInventoryComponent* InventoryComponent;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	/*UI Functions.*/
	void ToggleStorageWidget(AActor* StorageActorRef);
	void UpdateInventory();
	void ToggleInventory();
	void AddConditionIcon(AAbility* ConditionActorRef);
	void RemoveConditionIcon(AAbility* ConditionActorRef);
	void NotifyInteract(UObject* InObject);
	void UnnotifyInteract();
	void UpdateEquipment();
};
