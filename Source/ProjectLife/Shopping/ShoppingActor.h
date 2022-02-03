// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/InteractiveInterface.h"
#include "../Item/ItemStruct.h"
#include "GameFramework/Actor.h"
#include "ShoppingActor.generated.h"

class Aitem;
class UBoxComponent;
class UShoppingWidget;
class UDataTable;

UCLASS()
class PROJECTLIFE_API AShoppingActor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShoppingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* ShoppingCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shopping")
		TArray<FShopItemData> ShopItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shopping")
		TArray<FItemData> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TSubclassOf<UShoppingWidget> ShoppingWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Shopping")
		UShoppingWidget* ShoppingWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		UDataTable* ShoppingDataTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitShop();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);

	bool Transaction(int32 Quantity, int32 Index);
};
