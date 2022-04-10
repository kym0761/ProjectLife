// Fill out your copyright notice in the Description page of Project Settings.


#include "CookActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "../Base/BasicPlayerController.h"
#include "CookWidget.h"

// Sets default values
ACookActor::ACookActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StorageMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StorageMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StorageMesh);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

// Called when the game starts or when spawned
void ACookActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACookActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACookActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if Player's StorageUI is ON, Remove that.

	if (bOpen)
	{
		APawn* player = Cast<APawn>(OtherActor);
		if (player)
		{
			ABasicPlayerController* playerController = player->GetController<ABasicPlayerController>();
			if (playerController)
			{
				//playerController->ToggleStorageWidget(this);
				bOpen = false;
			}
		}
	}
}

void ACookActor::Interact_Implementation(APawn* InteractCauser)
{
	//Add To Viewport Storage UI.

	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();
	if (playerController)
	{
		//playerController->ToggleStorageWidget(this);

		if (bOpen)
		{
			bOpen = false;
		}
		else
		{
			bOpen = true;
		}
	}

	//CookWidget 생성

	if (!IsValid(CookWidgetClass))
	{
		return;
	}

	if (IsValid(CookWidgetRef))
	{
		CookWidgetRef->RemoveFromViewport();
	}

	CookWidgetRef = CreateWidget<UCookWidget>(playerController, CookWidgetClass);
	
	if (!IsValid(CookWidgetRef))
	{
		return;
	}

	CookWidgetRef->AddToViewport();
	CookWidgetRef->InitCookWidget(this);

}

bool ACookActor::MakeCooking(FString CookItemName)
{
	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return false;
	}

	FItemRecipeData* cookingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*CookItemName), "");

	//올바르지 않은 요리 레시피는 작동 불가능.
	if (cookingRecipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : no Recipe"));
		return false;
	}

	//실제로 재료들이 있는지 확인함. 전부 확인한 뒤에 요리를 시작할 수 있음.
	for (TPair<FString, int32> i : cookingRecipe->Recipe)
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
	for (TPair<FString, int32> i : cookingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //재료이름
		int32 ingredientQuantity = i.Value; //필요한 양

		InventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
	}

	FItemSlotData result;
	result.ItemName = cookingRecipe->ItemName;
	result.Quantity = cookingRecipe->Quantity;


	//10번째 inventory 공간에 아이템을 생성하도록 한다.
	InventoryComponent->SetInventoryItem(10, result);

	return true;
}

TArray<FItemRecipeData> ACookActor::CanMakeList()
{
	//만들 수 있는 요리 목록을 전달함.
	//위의 MakeCooking과 유사하게 인벤토리에 재료가 존재하는지 확인하고 가능한 레시피면 리스트에 넣어주고 전달.

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

