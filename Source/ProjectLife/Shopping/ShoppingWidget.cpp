// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "../Inventory/InventoryComponent.h"
#include "ShoppingActor.h"
#include "ShoppingSlot.h"
#include "Kismet/GameplayStatics.h"


void UShoppingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(MoneyTextBlock))
	{
		MoneyTextBlock->TextDelegate.BindDynamic(this, &UShoppingWidget::SetMoneyText);
		MoneyTextBlock->SynchronizeProperties();
	}

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UShoppingWidget::ExitButtonClicked);
	}
}

FText UShoppingWidget::SetMoneyText()
{
	if (IsValid(MoneyTextBlock))
	{
		UInventoryComponent* inventoryComponent = GetOwningPlayer()->FindComponentByClass<UInventoryComponent>();
		if (IsValid(inventoryComponent))
		{
			FString inText = FString("Your Money : ") + FString::FromInt(inventoryComponent->GetMoney());
			return FText::FromString(inText);
		}
	}

	return FText::GetEmpty();
}

void UShoppingWidget::ExitButtonClicked()
{
	GetOwningPlayer()->bShowMouseCursor = true;
	GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	RemoveFromViewport();
}

void UShoppingWidget::InitShoppingWidget(AShoppingActor* ShopOwner)
{
	if (IsValid(ShopOwner) && IsValid(ShoppingSlotClass))
	{
		ShoppingActorRef = ShopOwner;

		for (int32 i = 0; i < ShopOwner->Items.Num(); i++)
		{
			UShoppingSlot* slot = CreateWidget<UShoppingSlot>(GetOwningPlayer(), ShoppingSlotClass);
			ShoppingScrollBox->AddChild(slot);
			slot->InitShoppingSlot(ShopOwner, i);
		}
	}

}
