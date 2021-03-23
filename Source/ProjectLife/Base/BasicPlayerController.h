// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class ABasicCharacter;
class AAbility;
class UMainHUDBase;
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
		TSubclassOf<UMainHUDBase> MainHUDClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "UI")
		UMainHUDBase* MainHUDRef;


	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	void ToggleStorageWidget(AActor* StorageActorRef);

	void UpdateInventory();

	void AddConditionIcon(AAbility* ConditionActorRef);
	void RemoveConditionIcon(AAbility* ConditionActorRef);

	void ToggleInventory();

	void NotifyInteract(AActor* InActor);
	void UnnotifyInteract();

};
