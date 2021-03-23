// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/InventoryComponent.h"
#include "ShoppingActor.h"
#include "ShoppingSlotBase.h"

void UShoppingWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (MoneyTextBlock)
	{
		MoneyTextBlock->TextDelegate.BindDynamic(this, &UShoppingWidgetBase::SetMoneyText);
		MoneyTextBlock->SynchronizeProperties();
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UShoppingWidgetBase::ExitButtonClicked);
	}

	//test.. still not Complete..
	bIsFocusable = true;
}

FText UShoppingWidgetBase::SetMoneyText()
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

void UShoppingWidgetBase::ExitButtonClicked()
{
	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	RemoveFromViewport();
}

void UShoppingWidgetBase::InitShoppingWidget(AShoppingActor* ShopOwner)
{
	if (ShopOwner && ShoppingSlotClass)
	{
		for (int32 i = 0; i < ShopOwner->Items.Num(); i++)
		{
			UShoppingSlotBase* slot = CreateWidget<UShoppingSlotBase>(GetOwningPlayer(), ShoppingSlotClass);
			ShoppingScrollBox->AddChild(slot);
			slot->InitShoppingSlot(ShopOwner, i);
		}
	}

	//For Not Move while Shopping? Test.
	SetFocus();
}
