// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDBase.h"
#include "QuickSlotWidgetBase.h"
#include "../Inventory/InventoryWidgetBase.h"
#include "../Ability/ConditionWidgetBase.h"
#include "../Storage/StorageWidgetBase.h"
#include "Animation/WidgetAnimation.h"
#include "InteractNotifyWidgetBase.h"

void UMainHUDBase::NativeConstruct()
{
	Super::NativeConstruct();

	bInventoryUsing = false;
	bStorageUsing = false;
}

void UMainHUDBase::UpdateInventory()
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

void UMainHUDBase::ToggleInventory()
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

void UMainHUDBase::ToggleStorageWidget(AActor* StorageActorRef)
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


void UMainHUDBase::AddConditionIcon(AAbility* ConditionActorRef)
{
	if (Widget_Condition)
	{
		Widget_Condition->AddIcon(ConditionActorRef);
	}
}

void UMainHUDBase::RemoveConditionIcon(AAbility* ConditionActorRef)
{
	if (Widget_Condition)
	{
		Widget_Condition->RemoveIcon(ConditionActorRef);
	}
}

void UMainHUDBase::NotifyInteract(UObject* InObject)
{
	if (Widget_InteractNotify)
	{
		Widget_InteractNotify->NotifyInteract(InObject);
	}
}

void UMainHUDBase::UnnotifyInteract()
{
	if (Widget_InteractNotify)
	{
		Widget_InteractNotify->UnnotifyInteract();
	}
}
