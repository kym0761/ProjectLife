// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmShoppingBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
void UConfirmShoppingBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_OK)
	{
		Button_OK->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_OK);
	}

	if (Button_Cancel)
	{
		Button_Cancel->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_Cancel);
	}

	if (Button_Plus)
	{
		Button_Plus->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_Plus);
	}

	if (Button_10Plus)
	{
		Button_10Plus->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_10Plus);
	}

	if (Button_Minus)
	{
		Button_Minus->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_Minus);
	}

	if (Button_10Minus)
	{
		Button_10Minus->OnClicked.AddDynamic(this, &UConfirmShoppingBase::Clicked_10Minus);
	}

	if (TextBlock_Quantity)
	{
		TextBlock_Quantity->TextDelegate.BindDynamic(this, &UConfirmShoppingBase::SetQuantityText);
		TextBlock_Quantity->SynchronizeProperties();
	}

	Quantity = 0;
}

void UConfirmShoppingBase::Clicked_OK()
{
	//Transaction

	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (inventory)
	{
		FItemDataStruct temp = ItemData;
		temp.Quantity = Quantity;

		UE_LOG(LogTemp, Warning, TEXT(" ItemData Name : %s"), *temp.Name);

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

	}

	RemoveFromParent();
}

void UConfirmShoppingBase::Clicked_Cancel()
{
	RemoveFromParent();
}

void UConfirmShoppingBase::Clicked_Plus()
{
	int32 tempQuantity = Quantity + 1;
	bool bAffordable = false;
	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (inventory)
	{
		int32 tempPrice = tempQuantity * ItemData.ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ItemData.MaxQuantity);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("You Can't Buy. You Don't Have Enough Money"));
	}
}

void UConfirmShoppingBase::Clicked_10Plus()
{
	int32 tempQuantity = Quantity + 10;
	bool bAffordable = false;
	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (inventory)
	{
		int32 tempPrice = tempQuantity * ItemData.ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ItemData.MaxQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Can't Buy. You Don't Have Enough Money"));
	}
}

void UConfirmShoppingBase::Clicked_Minus()
{
	Quantity = FMath::Clamp(Quantity - 1, 0, ItemData.MaxQuantity);
}

void UConfirmShoppingBase::Clicked_10Minus()
{
	Quantity = FMath::Clamp(Quantity - 10, 0, ItemData.MaxQuantity);
}

FText UConfirmShoppingBase::SetQuantityText()
{
	return FText::FromString(FString::FromInt(Quantity));
}
