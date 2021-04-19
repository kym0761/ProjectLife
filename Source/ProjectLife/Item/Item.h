// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/InteractiveInterface.h"
#include "ItemStruct.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTLIFE_API AItem : public AActor , public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	//Needed for Main Collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		UBoxComponent* Collision;

	//Needed For Detection.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FItemDataStruct ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TSubclassOf<UItemData> ItemDataTest;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Pickup Item.
	void Interact_Implementation(APawn* InteractCauser);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category ="Item")
		bool UseItem();
		bool UseItem_Implementation();

};
