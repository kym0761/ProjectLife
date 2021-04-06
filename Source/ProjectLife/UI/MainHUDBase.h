// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDBase.generated.h"

class UQuickSlotWidgetBase;
class UInventoryWidgetBase;
class UConditionWidgetBase;
class UStorageWidgetBase;
class UInteractNotifyWidgetBase;

class UWidgetAnimation;

class AAbility;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UMainHUDBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UQuickSlotWidgetBase* Widget_QuickSlot;

	UPROPERTY(Meta = (BindWidget))
		UInventoryWidgetBase* Widget_Inventory;

	UPROPERTY(Meta = (BindWidget))
		UConditionWidgetBase* Widget_Condition;

	UPROPERTY(Meta = (BindWidget))
		UInteractNotifyWidgetBase* Widget_InteractNotify;

	UPROPERTY(Meta = (BindWidget))
		UStorageWidgetBase* Widget_Storage;


	UPROPERTY()
		bool bInventoryUsing;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* InventoryAnimation;

	UPROPERTY()
		bool bStorageUsing;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* StorageAnimation;



	virtual void NativeConstruct() override;

	void UpdateInventory();
	void ToggleInventory();

	void ToggleStorageWidget(AActor* StorageActorRef);

	void AddConditionIcon(AAbility* ConditionActorRef);
	void RemoveConditionIcon(AAbility* ConditionActorRef);


	void NotifyInteract(UObject* InObject);
	void UnnotifyInteract();

};
