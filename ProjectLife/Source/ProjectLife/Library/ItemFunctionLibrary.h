// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemFunctionLibrary.generated.h"

class AItem;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* WantToHeal : Link Actor Want to Heal.
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		static bool Heal(AActor* WantToHeal, float HealAmount);

	/**
	* WantToRefill : Link Actor Want to Refill Stamina.
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
		static bool RefillStamina(AActor* WantToRefill, float RefillAmount);
};
