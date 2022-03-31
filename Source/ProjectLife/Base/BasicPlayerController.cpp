// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "../Storage/StorageWidget.h"
#include "../Ability/ConditionWidget.h"
#include "../UI/MainHUD.h"
#include "../Inventory/InventoryComponent.h"

ABasicPlayerController::ABasicPlayerController()
{
	bShowMouseCursor = true;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void ABasicPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsLocalPlayerController())
	{
		return;
	}

	//When Possessed ABasicCharacter, Add SimpleUI & ConditionUI
	ABasicCharacter* player = Cast<ABasicCharacter>(InPawn);
	if (player)
	{
		if (IsValid(MainHUDClass))
		{
			MainHUDRef = CreateWidget<UMainHUD>(this, MainHUDClass);
			if (IsValid(MainHUDRef))
			{
				MainHUDRef->AddToViewport();
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, TEXT("Main UI Class Is Not Valid. if you see this, check the PlayerController's Class Reference"));
				}
			}
		}
	}

}

void ABasicPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	//Destroy UI When UnPossess

	if (IsValid(MainHUDRef))
	{
		MainHUDRef->RemoveFromParent();
		MainHUDRef = nullptr;
	}
}

void ABasicPlayerController::ToggleStorageWidget(AActor* StorageActorRef)
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->ToggleStorageWidget(StorageActorRef);
	}
}

//void ABasicPlayerController::UpdateInventory()
//{
//	if (IsValid(MainHUDRef))
//	{
//		MainHUDRef->UpdateInventory();
//	}
//}

void ABasicPlayerController::AddConditionIcon(AAbility* ConditionActorRef)
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->AddConditionIcon(ConditionActorRef);
	}
}

void ABasicPlayerController::RemoveConditionIcon(AAbility* ConditionActorRef)
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->RemoveConditionIcon(ConditionActorRef);
	}
}

void ABasicPlayerController::ToggleInventory()
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->ToggleInventory();
	}
}

void ABasicPlayerController::NotifyInteract(UObject* InObject)
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->NotifyInteract(InObject);
	}
}

void ABasicPlayerController::UnnotifyInteract()
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->UnnotifyInteract();
	}
}

void ABasicPlayerController::UpdateEquipment()
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->UpdateEquipment();
	}
}


