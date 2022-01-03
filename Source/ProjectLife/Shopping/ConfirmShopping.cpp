// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmShopping.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
#include "ShoppingActor.h"

void UConfirmShopping::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Button_OK))
	{
		Button_OK->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_OK);
	}

	if (IsValid(Button_Cancel))
	{
		Button_Cancel->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Cancel);
	}

	if (IsValid(Button_Plus))
	{
		Button_Plus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Plus);
	}

	if (IsValid(Button_10Plus))
	{
		Button_10Plus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_10Plus);
	}

	if (IsValid(Button_Minus))
	{
		Button_Minus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_Minus);
	}

	if (IsValid(Button_10Minus))
	{
		Button_10Minus->OnClicked.AddDynamic(this, &UConfirmShopping::Clicked_10Minus);
	}

	if (IsValid(TextBlock_Quantity))
	{
		TextBlock_Quantity->TextDelegate.BindDynamic(this, &UConfirmShopping::SetQuantityText);
		TextBlock_Quantity->SynchronizeProperties();
	}

}

void UConfirmShopping::Clicked_OK()
{
	//Transaction

	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
	if (IsValid(inventory))
	{
		//TODO : Transaction move to ShoppingActor
		bool bSucceed = ShopOwnerRef->Transaction(inventory, Quantity, ItemIndex);
		if (bSucceed)
		{
			ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
			if (IsValid(playerController))
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
	if (IsValid(inventory))
	{
		int32 tempPrice = tempQuantity * ShopOwnerRef->Items[ItemIndex].ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ShopOwnerRef->Items[ItemIndex].MaxQuantity);
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
	if (IsValid(inventory))
	{
		int32 tempPrice = tempQuantity * ShopOwnerRef->Items[ItemIndex].ItemPrice;
		bAffordable = inventory->CheckEnoughMoney(tempPrice);
	}

	if (bAffordable)
	{
		Quantity = FMath::Clamp(tempQuantity, 0, ShopOwnerRef->Items[ItemIndex].MaxQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Can't Buy. You Don't Have Enough Money"));
	}
}

void UConfirmShopping::Clicked_Minus()
{
	Quantity = FMath::Clamp(Quantity - 1, 0, ShopOwnerRef->Items[ItemIndex].MaxQuantity);
}

void UConfirmShopping::Clicked_10Minus()
{
	Quantity = FMath::Clamp(Quantity - 10, 0, ShopOwnerRef->Items[ItemIndex].MaxQuantity);
}

FText UConfirmShopping::SetQuantityText()
{
	return FText::FromString(FString::FromInt(Quantity));
}

void UConfirmShopping::InitConfirmShopping(AShoppingActor* ShopOwner, int32 Index)
{
	if (IsValid(ShopOwner) && ShopOwner->Items.IsValidIndex(Index))
	{
		ShopOwnerRef = ShopOwner;
		ItemIndex = Index;
	}
	else // if not valid, Delete.
	{
		RemoveFromParent();
	}
}
