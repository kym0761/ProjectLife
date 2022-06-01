// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../GamePlay/ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AItem::UseItem_Implementation()
{
	FItemData itemdata;
	
	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(gameInstance))
	{
		itemdata = gameInstance->GetItemDataFromTable(ItemName);
	
		switch (itemdata.ItemType)
		{
		case EItemType::Consumption:
			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Consumption"));
			SetLifeSpan(0.1f);
			break;
		case EItemType::Equipment:
			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Equipment"));
			SetLifeSpan(0.1f);
			break;
		case EItemType::Resource:
			UE_LOG(LogTemp, Warning, TEXT("Resource Item Will not Need Use Item function Maybe..?"));
			SetLifeSpan(0.1f);
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("I don't Know.."));
			SetLifeSpan(0.1f);
			break;
		}

		return true;
	}

	return false;
}

