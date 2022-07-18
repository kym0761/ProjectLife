// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFunctionLibrary.h"
#include "Base/StatComponent.h"
#include "Item/Item.h"
#include "Kismet/GameplayStatics.h"

bool UItemFunctionLibrary::Heal(AActor* WantToHeal, float HealAmount)
{
	if (IsValid(WantToHeal))
	{
		UStatComponent* statComp = WantToHeal->FindComponentByClass<UStatComponent>();
		if (statComp)
		{
			statComp->Heal(HealAmount);
			return true;
		}
	}
	return false;
}

bool UItemFunctionLibrary::RefillStamina(AActor* WantToRefill, float RefillAmount)
{
	if (IsValid(WantToRefill))
	{
		UStatComponent* statComp = WantToRefill->FindComponentByClass<UStatComponent>();
		if (statComp)
		{
			statComp->Heal(RefillAmount);
			return true;
		}
	}
	return false;
}
