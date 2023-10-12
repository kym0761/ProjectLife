// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftComponent.h"
#include "Inventory/InventoryComponent.h"


// Sets default values for this component's properties
UCraftComponent::UCraftComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCraftComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCraftComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCraftComponent::CheckCanMake(FString ItemNameToCraft)
{
	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return false;
	}

	FItemRecipeData* craftingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*ItemNameToCraft), "");

	//올바르지 않은 요리 레시피는 작동 불가능.
	if (craftingRecipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : no Recipe"));
		return false;
	}

	AActor* owner = GetOwner();
	if (!IsValid(owner))
	{
		//owner not valid
		return false;
	}

	UInventoryComponent* inventoryComponent = owner->FindComponentByClass<UInventoryComponent>();
	if (!IsValid(inventoryComponent))
	{
		// inventory not valid
		return false;
	}

	bool bHasSpace = inventoryComponent->CheckInventoryHasSpace();
	bool bPotentiallyHasSpace = false;

	//실제로 재료들이 있는지 확인함. 전부 확인한 뒤에 요리를 시작할 수 있음.
	for (TPair<FString, int32> i : craftingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //재료이름
		int32 ingredientQuantity = i.Value; //필요한 양

		bool bCheckHasEnoughIngredient = inventoryComponent->CheckItemInInventory(ingredientName, ingredientQuantity);

		if (bCheckHasEnoughIngredient == false) //재료 부족시 false.
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning : no enough Ingredient"));
			return false;
		}

		int32 currentQuantity = inventoryComponent->GetItemQuantity(ingredientName);
		if (currentQuantity == ingredientQuantity)
		{
			bPotentiallyHasSpace = true;
		}
	}


	//아이템을 소모하면 공간이 생길 수도 있거나, 혹은 원래 공간이 충분히 있다면 true. 그게 아니면 false.
	return bPotentiallyHasSpace || bHasSpace;
}

void UCraftComponent::StartCrafting(FString ItemNameToCraft, bool bSlotDecide, int32 SlotNum)
{
	FItemRecipeData* recipeData = GetRecipeDataFromDataTable(ItemNameToCraft);
	if (recipeData == nullptr)
	{
		return;
	}

	Progress = 0.0f;

	//Timer의 기능에 Parameter 추가하기 위해 델리게이트 선언
	FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &UCraftComponent::WhileCrafting, *recipeData, bSlotDecide, SlotNum);

	// 1/60초마다 Timer가 진행되도록 함.
	float interval = 1 / 60.0f;

	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().SetTimer(CraftTimer, timerDelegate, interval, true);
	}
}

void UCraftComponent::WhileCrafting(FItemRecipeData RecipeData, bool bSlotDecide, int32 SlotNum)
{
	//만약 Progress가 LeadTime만큼 진행됐다면 타이머를 종료하고 완성으로 넘어감
	if (Progress >= RecipeData.LeadTime)
	{
		if (IsValid(GetWorld()))
		{
			GetWorld()->GetTimerManager().ClearTimer(CraftTimer);
		}
		FinishCrafting(RecipeData.ItemName, bSlotDecide, SlotNum);
	}

	//Widget이 없어도 제작은 진행됨.
	Progress += 1 / 60.0f;

	//UI의 Progress 반영
	if(OnCrafting.IsBound())
	{
		OnCrafting.Broadcast(Progress/RecipeData.LeadTime);
	}
	
}

void UCraftComponent::FinishCrafting(FString ItemNameToCraft, bool bSlotDecide, int32 SlotNum)
{
	Crafting(ItemNameToCraft, true, 10);

	//초기화
	Progress = 0.0f;

	//UI의 Progress 초기화.
	if (OnCrafting.IsBound())
	{
		OnCrafting.Broadcast(0.0f);
	}

}

void UCraftComponent::Crafting(FString ItemNameToCraft, bool bSlotDecide, int32 SlotNum)
{
	FItemRecipeData recipeData = *GetRecipeDataFromDataTable(ItemNameToCraft);

	AActor* owner = GetOwner();
	if (!IsValid(owner))
	{
		//owner not valid
		return;
	}

	UInventoryComponent* inventoryComponent = owner->FindComponentByClass<UInventoryComponent>();
	if (!IsValid(inventoryComponent))
	{
		// inventory not valid
		return;
	}

	//실제로 아이템을 소비함. 이미 이전에 존재 자체를 이미 체크했으므로, 소비시 체크를 굳이 하지 않음.
	bool bCanMake = CheckCanMake(ItemNameToCraft);
	if (bCanMake)
	{
		for (TPair<FString, int32> i : recipeData.Recipe)
		{
			FString ingredientName = i.Key; //재료이름
			int32 ingredientQuantity = i.Value; //필요한 양

			inventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
		}
	}

	//완성품
	FItemSlotData result;
	result.ItemName = recipeData.ItemName;
	result.Quantity = recipeData.Quantity;

	if (bSlotDecide)
	{
		//정해진 슬롯이 있다면 그 슬롯 번호에 inventory 공간에 아이템을 생성하도록 한다.
		inventoryComponent->SetInventoryItem(SlotNum, result);
	}
	else
	{
		//정해진 슬롯이 없다면 빈 공간에 아이템 생성함.
		//AddItemToInventory는 아이템 공간 확보 유무 처리가 되어 있음.
		inventoryComponent->AddItemToInventory(result);
	}
	
}

FItemRecipeData* UCraftComponent::GetRecipeDataFromDataTable(FString ItemNameToCraft)
{

	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return nullptr;
	}

	FItemRecipeData* craftingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*ItemNameToCraft), "");
	
	return craftingRecipe;
}

TArray<FItemRecipeData> UCraftComponent::GetCanMakeList() const
{
	//만들 수 있는 요리 목록을 UI에 전달함.
	//위의 Crafting과 유사하게 인벤토리에 재료가 존재하는지 확인하고 가능한 레시피면 리스트에 넣어주고 전달.
	TArray<FItemRecipeData> result;

	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return result; // empty list
	}

	AActor* owner = GetOwner();
	if (!IsValid(owner))
	{
		//owner not valid
		return result;
	}

	UInventoryComponent* inventoryComponent = owner->FindComponentByClass<UInventoryComponent>();
	if (!IsValid(inventoryComponent))
	{
		// inventory not valid
		return result;
	}

	TArray<FItemRecipeData*> arr;
	RecipeDataTable->GetAllRows<FItemRecipeData>("", arr);

	for (FItemRecipeData* recipeItem : arr)
	{
		if (recipeItem == nullptr)
		{
			continue;
		}

		bool bCanMake = true;

		for (TPair<FString, int32> i : recipeItem->Recipe)
		{
			FString ingredientName = i.Key; //재료이름
			int32 ingredientQuantity = i.Value; //필요한 양

			bool bCheckHasEnoughIngredient = inventoryComponent->CheckItemInInventory(ingredientName, ingredientQuantity);

			if (bCheckHasEnoughIngredient == false)
			{
				bCanMake = false;
				break;
			}
		}

		//제작이 가능한 아이템은 목록에 추가함.
		if (bCanMake)
		{
			result.Add(*recipeItem);
		}
	}

	return result;
}

