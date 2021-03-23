// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/Base.h"
#include "../Item/ItemStruct.h"
#include "GameFramework/Actor.h"
#include "ShoppingActor.generated.h"

class Aitem;
class UBoxComponent;
class UShoppingWidgetBase;

UCLASS()
class PROJECTLIFE_API AShoppingActor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShoppingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* ShoppingCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TArray<TSubclassOf<AItem>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
		TSubclassOf<UShoppingWidgetBase> ShoppingWidgetClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Shopping")
		UShoppingWidgetBase* ShoppingWidgetRef;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);
};
