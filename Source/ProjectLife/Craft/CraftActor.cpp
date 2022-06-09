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
	//TODO : EndOverlap�� �Ǹ� ������̴� CraftActor UI�� �����Ͽ� ��� �÷��̷� ���ư� �� �ְ� ��.
	// �ʿ���� �ȴٸ� ���� �ȸ��� ��.

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

	//CraftWidget ����

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

	//�ùٸ��� ���� �丮 �����Ǵ� �۵� �Ұ���.
	if (craftingRecipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : no Recipe"));
		return false;
	}

	//������ ������ �ִ��� Ȯ����. ���� Ȯ���� �ڿ� �丮�� ������ �� ����.
	for (TPair<FString, int32> i : craftingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //����̸�
		int32 ingredientQuantity = i.Value; //�ʿ��� ��

		bool bCheckHasEnoughIngredient = InventoryComponent->CheckItemInInventory(ingredientName, ingredientQuantity);

		if (bCheckHasEnoughIngredient == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Warning : no enough Ingredient"));
			return false;
		}
	}

	//������ �������� �Һ���. ������ ���� ��ü�� �̹� üũ�����Ƿ�, �Һ�� üũ�� ���� ���� ����.
	for (TPair<FString, int32> i : craftingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //����̸�
		int32 ingredientQuantity = i.Value; //�ʿ��� ��

		InventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
	}

	FItemSlotData result;
	result.ItemName = craftingRecipe->ItemName;
	result.Quantity = craftingRecipe->Quantity;


	//10��° inventory ������ �������� �����ϵ��� �Ѵ�.
	InventoryComponent->SetInventoryItem(10, result);

	return true;
}

TArray<FItemRecipeData> ACraftActor::GetCanMakeList() const
{
	//���� �� �ִ� �丮 ����� UI�� ������.
	//���� Crafting�� �����ϰ� �κ��丮�� ��ᰡ �����ϴ��� Ȯ���ϰ� ������ �����Ǹ� ����Ʈ�� �־��ְ� ����.

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
			FString ingredientName = i.Key; //����̸�
			int32 ingredientQuantity = i.Value; //�ʿ��� ��

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

