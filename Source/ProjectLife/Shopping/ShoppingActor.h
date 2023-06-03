// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/InteractiveInterface.h"
#include "Item/ItemStruct.h"
#include "GameFramework/Actor.h"
#include "ShoppingActor.generated.h"

class Aitem;
class UBoxComponent;
class UShoppingWidget;
class UDataTable;
class UInventoryComponent;

UCLASS()
class PROJECTLIFE_API AShoppingActor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShoppingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UBoxComponent> ShoppingCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TSubclassOf<UShoppingWidget> ShoppingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TObjectPtr<UDataTable> ShoppingDataTable;

	UPROPERTY()
		TObjectPtr<UShoppingWidget> ShoppingWidgetRef;

	//구매 목록 Cache
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shopping", Meta = (AllowPrivateAccess = "true"))
		TArray<FItemData> Items;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitShop();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);

	bool Transaction(UInventoryComponent* InventoryComponent, int32 Index, int32 Quantity);
};
