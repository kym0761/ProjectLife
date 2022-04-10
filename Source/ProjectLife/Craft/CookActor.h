// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Item/ItemStruct.h"
#include "../Base/InteractiveInterface.h"
#include "CookActor.generated.h"

class UInventoryComponent;
class USphereComponent;
class USkeletalMeshComponent;
class UDataTable;
class UCookWidget;
UCLASS()
class PROJECTLIFE_API ACookActor : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* Sphere;

	//StorageMesh will be SkeletalMesh because of "Open or Close"
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* StorageMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cook")
		UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		UDataTable* RecipeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cook")
		TSubclassOf<UCookWidget> CookWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cook")
		bool bOpen;

private:

	UPROPERTY()
		UCookWidget* CookWidgetRef;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void Interact_Implementation(APawn* InteractCauser);

	bool MakeCooking(FString CookItemName);

	TArray<FItemRecipeData> CanMakeList();
};
