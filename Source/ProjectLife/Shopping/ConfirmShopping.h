// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmShopping.generated.h"

class UButton;
class UTextBlock;
class AShoppingActor;
class UInventoryComponent;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UConfirmShopping : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_OK;
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_Cancel;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_Plus;
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_10Plus;
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_Minus;
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> Button_10Minus;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Quantity;

private:

	//UI 상에서 나타나는 구매하고 싶은 양.
	UPROPERTY()
		int32 Quantity;

	UPROPERTY()
		TObjectPtr<AShoppingActor> ShopOwnerRef;

	UPROPERTY()
		TObjectPtr<UInventoryComponent> InventoryComponentRef;


	//가리키고 있는 상점의 아이템 Array Number
	UPROPERTY()
		int32 ShopItemIndex;

public:

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

protected:

	virtual bool Initialize() override;

};
