// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemStruct.h"
#include "CraftComponent.generated.h"

class UDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrafting, float, InProgress);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UCraftComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UCraftComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
		UDataTable* RecipeDataTable;

private:
	UPROPERTY()
		float Progress;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckCanMake(FString ItemNameToCraft);

	void StartCrafting(FString ItemNameToCraft, bool bSlotDecide = false, int32 SlotNum = 10);

	FTimerHandle CraftTimer;
	void WhileCrafting(FItemRecipeData RecipeData, bool bSlotDecide = false, int32 SlotNum = 10);

	FOnCrafting OnCrafting;
	void FinishCrafting(FString ItemNameToCraft, bool bSlotDecide = false, int32 SlotNum = 10);

	//bSlotDecide는 원하는 슬롯에 아이템을 생성하고 싶을 때 쓴다.
	//SlotNum 정할 수 있지만, CraftActor 기준 10번을 씀.
	void Crafting(FString ItemNameToCraft, bool bSlotDecide = false, int32 SlotNum = 10);

	FItemRecipeData* GetRecipeDataFromDataTable(FString ItemNameToCraft);

	TArray<FItemRecipeData> GetCanMakeList() const;
};
