// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CookWidget.generated.h"

class UItemSlot;
class UButton;
class ACookActor;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cook")
		ACookActor* CookActorRef;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void InitCookWidget();

	void UpdateCookWidget();

	UFUNCTION()
		void Clicked_DoCooking();

};
