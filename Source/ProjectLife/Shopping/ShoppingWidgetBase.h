// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShoppingWidgetBase.generated.h"

class UScrollBox;
class UTextBlock;
class UButton;
class AShoppingActor;
class UShoppingSlotBase;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UShoppingWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ShoppingScrollBox;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* MoneyTextBlock;

	UPROPERTY(Meta = (BindWidget))
		UButton* ExitButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Button")
		AShoppingActor* ShoppingActorRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		TSubclassOf<UShoppingSlotBase> ShoppingSlotClass;

	virtual void NativeConstruct() override;

	UFUNCTION()
		FText SetMoneyText();

	UFUNCTION()
		void ExitButtonClicked();

	void InitShoppingWidget(AShoppingActor* ShopOwner);
};
