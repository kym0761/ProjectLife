// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftWidget.generated.h"

class UItemSlot;
class UButton;
class ACraftActor;
class UVerticalBox;
class UCraftSelectionSlot;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCraftWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY()
		TArray<UItemSlot*> ItemSlotArray;

	UPROPERTY(Meta = (BindWidget))
		UItemSlot* ItemSlot_Result;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_DoCrafting;

	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* VerticalBox_CanDo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		TSubclassOf<UCraftSelectionSlot> CraftSelectionSlotClass;

private:

	UPROPERTY()
		ACraftActor* CraftActorRef;

	UPROPERTY()
		FString CraftResultName;

public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void InitCraftWidget(ACraftActor* CraftActor);

	UFUNCTION()
		void UpdateCraftWidget();

	UFUNCTION()
		void Clicked_DoCrafting();

	void UpdateSelections();

	void SetCraftResultName(FString InVal);
};
