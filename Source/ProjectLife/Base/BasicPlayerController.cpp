// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayerController.h"
#include "BasicCharacter.h"
#include "../Storage/StorageWidgetBase.h"
#include "../Ability/ConditionWidgetBase.h"
#include "../Inventory/InventoryComponent.h"
#include "../UI/MainHUDBase.h"

ABasicPlayerController::ABasicPlayerController()
{
	bShowMouseCursor = true;
	
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
			MainHUDRef = CreateWidget<UMainHUDBase>(this, MainHUDClass);
			if (IsValid(MainHUDRef))
			{
				MainHUDRef->AddToViewport();

				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.5f,FColor::Black,TEXT("Main UI ON"));
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

void ABasicPlayerController::UpdateInventory()
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->UpdateInventory();
	}
}

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

void ABasicPlayerController::NotifyInteract(AActor* InActor)
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->NotifyInteract(InActor);
	}
}

void ABasicPlayerController::UnnotifyInteract()
{
	if (IsValid(MainHUDRef))
	{
		MainHUDRef->UnnotifyInteract();
	}
}
