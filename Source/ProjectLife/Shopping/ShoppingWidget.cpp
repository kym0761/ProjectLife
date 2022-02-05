// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "../Inventory/InventoryManager.h"
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
		AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));
		if (IsValid(inventoryManager))
		{
			FString inText = FString("Your Money : ") + FString::FromInt(inventoryManager->Money);
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
		for (int32 i = 0; i < ShopOwner->Items.Num(); i++)
		{
			UShoppingSlot* slot = CreateWidget<UShoppingSlot>(GetOwningPlayer(), ShoppingSlotClass);
			ShoppingScrollBox->AddChild(slot);
			slot->InitShoppingSlot(ShopOwner, i);
		}
	}

}
