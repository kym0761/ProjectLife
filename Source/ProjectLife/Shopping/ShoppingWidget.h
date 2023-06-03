// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShoppingWidget.generated.h"

class UScrollBox;
class UTextBlock;
class UButton;
class AShoppingActor;
class UShoppingSlot;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UShoppingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UScrollBox> ShoppingScrollBox;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> MoneyTextBlock;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UButton> ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TSubclassOf<UShoppingSlot> ShoppingSlotClass;

private:

	UPROPERTY()
		TObjectPtr<AShoppingActor> ShoppingActorRef;

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
		FText SetMoneyText();

	UFUNCTION()
		void ExitButtonClicked();

	void InitShoppingWidget(AShoppingActor* ShopOwner);

protected:

	virtual bool Initialize() override;

};
