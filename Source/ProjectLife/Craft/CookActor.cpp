// Fill out your copyright notice in the Description page of Project Settings.


#include "CookActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "../Base/BasicPlayerController.h"
#include "../Item/ItemStruct.h"

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
}

bool ACookActor::MakeCooking()
{
	//TODO : 요리할 아이템 이름 외부에서 받아오기

	FString tempDishItemName = "Stirred-Carrot";

	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return false;
	}

	FItemRecipeData* cookingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*tempDishItemName), "");

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

	FItemDataSlot result;
	result.ItemName = cookingRecipe->ItemName;
	result.Quantity = cookingRecipe->Quantity;

	//TODO : 결과물은 어떻게 처리해야하는지?
	//10번째 inventory 공간에 아이템을 생성하도록 한다.
	InventoryComponent->SetInventoryItem(10, result);

	return true;
}

