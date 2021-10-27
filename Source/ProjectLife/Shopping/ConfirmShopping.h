// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmShopping.generated.h"

class UButton;
class UTextBlock;
class AShoppingActor;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConfirmShopping : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_OK;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Cancel;

	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Plus;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_10Plus;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Minus;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_10Minus;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Quantity;

	UPROPERTY()
		int32 Quantity;

	UPROPERTY()
		AShoppingActor* ShopOwnerRef;
	UPROPERTY()
		int32 ItemIndex;

	virtual void NativeConstruct() override;


	UFUNCTION()
		void Clicked_OK();
	UFUNCTION()
		void Clicked_Cancel();
	UFUNCTION()
		void Clicked_Plus();
	UFUNCTION()
		void Clicked_10Plus();
	UFUNCTION()
		void Clicked_Minus();
	UFUNCTION()
		void Clicked_10Minus();
	UFUNCTION()
		FText SetQuantityText();

	void InitConfirmShopping(AShoppingActor* ShopOwner, int32 Index);

};
