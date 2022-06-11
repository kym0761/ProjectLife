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
	Progress = 0.0f;
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

	//CraftWidget 생성 전 확인
	if (!IsValid(CraftWidgetClass))
	{
		return;
	}

	//기존에 있던 CraftWidget 제거
	if (IsValid(CraftWidgetRef))
	{
		CraftWidgetRef->RemoveFromViewport();
	}

	//생성
	CraftWidgetRef = CreateWidget<UCraftWidget>(playerController, CraftWidgetClass);

	if (!IsValid(CraftWidgetRef))
	{
		return;
	}

	CraftWidgetRef->AddToViewport();
	CraftWidgetRef->InitCraftWidget(this);

}

void ACraftActor::Crafting(FString ItemNameToCraft)
{
	if (bCanUse == false)
	{
		//제작 중이므로 제작 요청을 받고 있으면 안됨.
		return;
	}


	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		//return false;
		return;
	}

	FItemRecipeData* craftingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*ItemNameToCraft), "");

	//올바르지 않은 요리 레시피는 작동 불가능.
	if (craftingRecipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : no Recipe"));
		//return false;
		return;
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
			//return false;
			return;
		}
	}

	//제작 시작
	StartCrafting(*craftingRecipe);

}

void ACraftActor::StartCrafting(FItemRecipeData RecipeData)
{
	//다른 제작을 할 수 없게 막음
	bCanUse = false;

	//초기화
	if (IsValid(CraftWidgetRef))
	{
		CraftWidgetRef->SetProgress(0.0f);
	}
	Progress = 0.0f;

	//Timer의 기능에 Parameter 추가하기 위해 델리게이트 선언
	FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(this, &ACraftActor::WhileCrafting, RecipeData);

	// 1/60초마다 Timer가 진행되도록 함.
	float interval = 1 / 60.0f;
	GetWorldTimerManager().SetTimer(CraftTimer, timerDelegate, interval, true);

}

void ACraftActor::WhileCrafting(FItemRecipeData RecipeData)
{
	//만약 Progress가 LeadTime만큼 진행됐다면 타이머를 종료하고 완성으로 넘어감
	if (Progress >= RecipeData.LeadTime)
	{
		GetWorldTimerManager().ClearTimer(CraftTimer);
		FinishCrafting(RecipeData);
	}

	//Widget이 없어도 제작은 진행됨.
	Progress += 1 / 60.0f;

	//CraftWidget이 없으면 CraftWidget의 Progress 기능은 멈춰야함.
	if (!IsValid(CraftWidgetRef))
	{
		return;
	}
	CraftWidgetRef->SetProgress(Progress / RecipeData.LeadTime);
}

void ACraftActor::FinishCrafting(FItemRecipeData RecipeData)
{
	//실제로 아이템을 소비함. 이미 이전에 존재 자체를 이미 체크했으므로, 소비시 체크를 굳이 하지 않음.
	for (TPair<FString, int32> i : RecipeData.Recipe)
	{
		FString ingredientName = i.Key; //재료이름
		int32 ingredientQuantity = i.Value; //필요한 양

		InventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
	}

	//완성품
	FItemSlotData result;
	result.ItemName = RecipeData.ItemName;
	result.Quantity = RecipeData.Quantity;

	//10번째 inventory 공간에 아이템을 생성하도록 한다.
	InventoryComponent->SetInventoryItem(10, result);

	//초기화
	bCanUse = true;
	Progress = 0.0f;

	if (!IsValid(CraftWidgetRef))
	{
		return;
	}
	CraftWidgetRef->SetProgress(Progress);
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

		//제작이 가능한 아이템은 목록에 추가함.
		if (bCanMake)
		{
			result.Add(*recipeItem);
		}
	}

	return result;
}

