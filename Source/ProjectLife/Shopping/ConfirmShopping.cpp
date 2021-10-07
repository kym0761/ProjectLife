// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmShopping.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicPlayerController.h"

void UConfirmShopping::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_OK)
	{
		Button_OK->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_OK);
	}

	if (Button_Cancel)
	{
		Button_Cancel->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Cancel);
	}

	if (Button_Plus)
	{
		Button_Plus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Plus);
	}

	if (Button_10Plus)
	{
		Button_10Plus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_10Plus);
	}

	if (Button_Minus)
	{
		Button_Minus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Minus);
	}

	if (Button_10Minus)
	{
		Button_10Minus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_10Minus);
	}

	if (TextBlock_Quantity)
	{
		TextBlock_Quantity->TextDelegate.BindDynamic(this, &UConfirmShopping::SetQuantityText);
		TextBlock_Quantity->SynchronizeProperties();
	}

	Quantity = 0;
}

void UConfirmShopping::Clicked_OK()
{
	//Transaction

	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (IsValid(inventory))
	{
		FItemDataSlot temp = ItemDataSlot;
		temp.Quantity = Quantity;

		//UE_LOG(LogTemp, Warning, TEXT(" ItemData Name : %s"), *temp.ItemData.GetDefaultObject()->Name);

		bool bSucceed = inventory->Transaction(temp);
		if (bSucceed)
		{
			ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
			if (playerController)
			{
				playerController->UpdateInventory();
			}
		}
	}
	else 
	{
		//what?
	}

	RemoveFromParent();
}

void UConfirmShopping::Clicked_Cancel()
{
	RemoveFromParent();
}

void UConfirmShopping::Clicked_Plus()
{
	int32 tempQuantity = Quantity + 1;
	bool bAffordable = false;
	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (inventory)
	{
		int32 tempPrice = tempQuantity * ItemDataSlot.ItemData.GetDefaultObject()->ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ItemDataSlot.ItemData.GetDefaultObject()->MaxQuantity);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("You Can't Buy. You Don't Have Enough Money"));
	}
}

void UConfirmShopping::Clicked_10Plus()
{
	int32 tempQuantity = Quantity + 10;
	bool bAffordable = false;
	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (inventory)
	{
		int32 tempPrice = tempQuantity * ItemDataSlot.ItemData.GetDefaultObject()->ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ItemDataSlot.ItemData.GetDefaultObject()->MaxQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Can't Buy. You Don't Have Enough Money"));
	}
}

void UConfirmShopping::Clicked_Minus()
{
	Quantity = FMath::Clamp(Quantity - 1, 0, ItemDataSlot.ItemData.GetDefaultObject()->MaxQuantity);
}

void UConfirmShopping::Clicked_10Minus()
{
	Quantity = FMath::Clamp(Quantity - 10, 0, ItemDataSlot.ItemData.GetDefaultObject()->MaxQuantity);
}

FText UConfirmShopping::SetQuantityText()
{
	return FText::FromString(FString::FromInt(Quantity));
}
