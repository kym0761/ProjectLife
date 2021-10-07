// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/InventoryComponent.h"
#include "ShoppingActor.h"
#include "ShoppingSlot.h"

void UShoppingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MoneyTextBlock)
	{
		MoneyTextBlock->TextDelegate.BindDynamic(this, &UShoppingWidget::SetMoneyText);
		MoneyTextBlock->SynchronizeProperties();
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UShoppingWidget::ExitButtonClicked);
	}

	//test.. still not Complete..
	bIsFocusable = true;
}

FText UShoppingWidget::SetMoneyText()
{
	if (MoneyTextBlock)
	{
		ABasicCharacter* playerCharacter = GetOwningPlayerPawn<ABasicCharacter>();
		if (playerCharacter)
		{
			UInventoryComponent* inventory = playerCharacter->Inventory;
			if (inventory)
			{
				FString inText = FString("Your Money : ") + FString::FromInt(inventory->Money);

				return FText::FromString(inText);
			}
		}
	}

	return FText::GetEmpty();
}

void UShoppingWidget::ExitButtonClicked()
{
	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	RemoveFromViewport();
}

void UShoppingWidget::InitShoppingWidget(AShoppingActor* ShopOwner)
{
	if (ShopOwner && ShoppingSlotClass)
	{
		for (int32 i = 0; i < ShopOwner->Items.Num(); i++)
		{
			UShoppingSlot* slot = CreateWidget<UShoppingSlot>(GetOwningPlayer(), ShoppingSlotClass);
			ShoppingScrollBox->AddChild(slot);
			slot->InitShoppingSlot(ShopOwner, i);
		}
	}

	//For Not Move while Shopping? Test.
	SetFocus();
}
