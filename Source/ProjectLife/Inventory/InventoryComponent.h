// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemDataSlot> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 InventoryCapacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 Money;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitInventory();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckInventoryHasSpace();


	bool AddItemToInventory(FItemDataSlot ItemDataSlot);
	bool AddItemToInventory(FString ItemName, int32 Quantity);


	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void PopItemFromInventory(int32 Index);

	bool SwapInventoryItem(int32 CurrentInventoryIndex, UInventoryComponent* OtherInventory, int32 OtherInventoryIndex);

	bool UseItemInInventory(int32 InventoryIndex);

	bool SpendMoney(int32 OutMoney);
	void GainMoney(int32 InMoney);

	bool CheckEnoughMoney(int32 ToCompare);

	bool Transaction(FItemDataSlot InValue);

};
