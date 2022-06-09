// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicPlayerController.h"
#include "CraftWidget.h"

// Sets default values
ACraftActor::ACraftActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	bCanUse = true;
}

// Called when the game starts or when spawned
void ACraftActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraftActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO : EndOverlap이 되면 사용중이던 CraftActor UI를 삭제하여 평소 플레이로 돌아갈 수 있게 함.
	// 필요없게 된다면 굳이 안만들어도 됨.

}

void ACraftActor::Interact_Implementation(APawn* InteractCauser)
{

	//Add To Viewport Storage UI.

	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();
	if (!IsValid(playerController))
	{
		//controller failed
		return;
	}
	//if (playerController)
	//{
	//	//playerController->ToggleStorageWidget(this);

	//	if (bOpen)
	//	{
	//		bOpen = false;
	//	}
	//	else
	//	{
	//		bOpen = true;
	//	}
	//}

	//CraftWidget 생성

	if (!IsValid(CraftWidgetClass))
	{
		return;
	}

	if (IsValid(CraftWidgetRef))
	{
		CraftWidgetRef->RemoveFromViewport();
	}

	CraftWidgetRef = CreateWidget<UCraftWidget>(playerController, CraftWidgetClass);

	if (!IsValid(CraftWidgetRef))
	{
		return;
	}

	CraftWidgetRef->AddToViewport();
	CraftWidgetRef->InitCraftWidget(this);



}

bool ACraftActor::Crafting(FString ItemNameToCraft)
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

	//실제로 재료들이 있는지 확인함. 전부 확인한 뒤에 요리를 시작할 수 있음.
	for (TPair<FString, int32> i : craftingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //재료이름
		int32 ingredientQuantity = i.Value; //필요한 양

		bool bCheckHasEnoughIngredient = InventoryComponent->CheckItemInInventory(ingredientName, ingredientQuantity);

		if (bCheckHasEnoughIngredient == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning : no enough Ingredient"));
			return false;
		}
	}

	//실제로 아이템을 소비함. 위에서 존재 자체를 이미 체크했으므로, 소비시 체크를 굳이 하지 않음.
	for (TPair<FString, int32> i : craftingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //재료이름
		int32 ingredientQuantity = i.Value; //필요한 양

		InventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
	}

	FItemSlotData result;
	result.ItemName = craftingRecipe->ItemName;
	result.Quantity = craftingRecipe->Quantity;


	//10번째 inventory 공간에 아이템을 생성하도록 한다.
	InventoryComponent->SetInventoryItem(10, result);

	return true;
}

TArray<FItemRecipeData> ACraftActor::GetCanMakeList() const
{
	//만들 수 있는 요리 목록을 UI에 전달함.
	//위의 Crafting과 유사하게 인벤토리에 재료가 존재하는지 확인하고 가능한 레시피면 리스트에 넣어주고 전달.

	TArray<FItemRecipeData> result;

	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return result; // empty list
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

			bool bCheckHasEnoughIngredient = InventoryComponent->CheckItemInInventory(ingredientName, ingredientQuantity);

			if (bCheckHasEnoughIngredient == false)
			{
				bCanMake = false;
				break;
			}
		}

		if (bCanMake)
		{
			result.Add(*recipeItem);
		}
	}

	return result;
}

