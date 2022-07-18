// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base/InteractiveInterface.h"
#include "ItemStruct.h"
#include "ItemPickup.generated.h"

class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;


UCLASS()
class PROJECTLIFE_API AItemPickup : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

	//Needed for Main Collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	//Needed For Detection.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", Meta = (AllowPrivateAccess = "true"))
		FItemSlotData ItemSlotData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Pickup Item.
	void Interact_Implementation(APawn* InteractCauser);

	//temporal Function for Random Generator
	void RandomItem();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	//	bool UseItem();
	//bool UseItem_Implementation();
};
