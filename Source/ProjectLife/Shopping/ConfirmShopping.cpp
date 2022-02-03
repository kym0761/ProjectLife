// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmShopping.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Base/BasicPlayerController.h"
#include "ShoppingActor.h"
#include "../Inventory/InventoryManager.h"
#include "Kismet/GameplayStatics.h"

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
	////Transaction

	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		bool bSucceed  = ShopOwnerRef->Transaction(Quantity, ItemIndex);
		if (bSucceed)
		{
			ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
			if (IsValid(playerController))
			{
				playerController->UpdateInventory();
			}
		}
	}

	//거래 완료가 됐든 실패가 됐든 기능 종료가 되면 사라짐.
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

	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		int32 tempPrice = tempQuantity * ShopOwnerRef->Items[ItemIndex].ItemPrice;
		bAffordable = inventoryManager->CheckEnoughMoney(tempPrice);
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

	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));
	if (IsValid(inventoryManager))
	{
		int32 tempPrice = tempQuantity * ShopOwnerRef->Items[ItemIndex].ItemPrice;
		bAffordable = inventoryManager->CheckEnoughMoney(tempPrice);
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
