// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "QuickSlotWidget.h"
#include "../Inventory/InventoryWidget.h"
#include "../Ability/ConditionWidget.h"
#include "../Storage/StorageWidget.h"
#include "Animation/WidgetAnimation.h"
#include "InteractNotifyWidget.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	bInventoryUsing = false;
	bStorageUsing = false;
}

void UMainHUD::UpdateInventory()
{
	if (IsValid(Widget_Inventory))
	{
		Widget_Inventory->UpdateInventoryWidget();
	}

	if (IsValid(Widget_QuickSlot))
	{
		Widget_QuickSlot->UpdateQuickSlot();
	}

	if (IsValid(Widget_Storage))
	{
		Widget_Storage->UpdateStorage();
	}

}

void UMainHUD::ToggleInventory()
{
	if (IsValid(InventoryAnimation))
	{
		if (bInventoryUsing)
		{
			bInventoryUsing = false;
			PlayAnimationReverse(InventoryAnimation);
		}
		else
		{
			bInventoryUsing = true;
			PlayAnimationForward(InventoryAnimation);
		}

	}
}

void UMainHUD::ToggleStorageWidget(AActor* StorageActorRef)
{
	if (IsValid(Widget_Storage) && IsValid(StorageAnimation))
	{
		if (bStorageUsing)
		{
			bStorageUsing = false;
			PlayAnimationReverse(StorageAnimation);
		}
		else
		{
			bStorageUsing = true;
			Widget_Storage->InitStorage(StorageActorRef);
			PlayAnimationForward(StorageAnimation);
		}
	}
}


void UMainHUD::AddConditionIcon(AAbility* ConditionActorRef)
{
	if (Widget_Condition)
	{
		Widget_Condition->AddIcon(ConditionActorRef);
	}
}

void UMainHUD::RemoveConditionIcon(AAbility* ConditionActorRef)
{
	if (Widget_Condition)
	{
		Widget_Condition->RemoveIcon(ConditionActorRef);
	}
}

void UMainHUD::NotifyInteract(UObject* InObject)
{
	if (Widget_InteractNotify)
	{
		Widget_InteractNotify->NotifyInteract(InObject);
	}
}

void UMainHUD::UnnotifyInteract()
{
	if (Widget_InteractNotify)
	{
		Widget_InteractNotify->UnnotifyInteract();
	}
}
