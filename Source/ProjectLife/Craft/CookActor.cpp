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
	//TODO : �丮�� ������ �̸� �ܺο��� �޾ƿ���

	FString tempDishItemName = "Stirred-Carrot";

	if (!IsValid(RecipeDataTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Recipe invalid"));
		return false;
	}

	FItemRecipeData* cookingRecipe = RecipeDataTable->FindRow<FItemRecipeData>(FName(*tempDishItemName), "");

	//�ùٸ��� ���� �丮 �����Ǵ� �۵� �Ұ���.
	if (cookingRecipe == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : no Recipe"));
		return false;
	}

	//������ ������ �ִ��� Ȯ����. ���� Ȯ���� �ڿ� �丮�� ������ �� ����.
	for (TPair<FString, int32> i : cookingRecipe->Recipe)
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
	for (TPair<FString, int32> i : cookingRecipe->Recipe)
	{
		FString ingredientName = i.Key; //����̸�
		int32 ingredientQuantity = i.Value; //�ʿ��� ��

		InventoryComponent->UseItemsInInventory(ingredientName, ingredientQuantity);
	}

	FItemDataSlot result;
	result.ItemName = cookingRecipe->ItemName;
	result.Quantity = cookingRecipe->Quantity;

	//TODO : ������� ��� ó���ؾ��ϴ���?
	//10��° inventory ������ �������� �����ϵ��� �Ѵ�.
	InventoryComponent->SetInventoryItem(10, result);

	return true;
}

