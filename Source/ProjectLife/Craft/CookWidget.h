// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CookWidget.generated.h"

class UItemSlot;
class UButton;
class ACookActor;
class UVerticalBox;
class UCookSelectionSlot;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCookWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		TArray<UItemSlot*> ItemSlotArray;

	UPROPERTY(Meta = (BindWidget))
	UItemSlot* ItemSlot_Result;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_DoCooking;

	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* VerticalBox_CanDo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		TSubclassOf<UCookSelectionSlot> CookSelectionSlotClass;

private:

	UPROPERTY()
		ACookActor* CookActorRef;

	UPROPERTY()
		FString CookResultName;

public:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void InitCookWidget(ACookActor* CookActor);

	UFUNCTION()
	void UpdateCookWidget();

	UFUNCTION()
		void Clicked_DoCooking();

	void UpdateSelections();

	void SetCookResultName(FString InVal);

};
