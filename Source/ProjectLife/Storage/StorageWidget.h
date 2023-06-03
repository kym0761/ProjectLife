// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageWidget.generated.h"

class UUniformGridPanel;
class UItemSlot;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UStorageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UUniformGridPanel> SlotGridPanel;

private:

	UPROPERTY()
		TArray<TObjectPtr<UItemSlot>> ItemSlotArray;

public:

	virtual void NativeConstruct() override;

	void InitStorageWidget(AActor* StorageActorRef);

	UFUNCTION(BlueprintCallable, Category = "Storage")
	void UpdateStorageWidget();
};
