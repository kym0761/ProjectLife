// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "../Base/BasicInteractiveActor.h"
#include "StorageBox.generated.h"

class UInventoryComponent;
class UStorageWidgetBase;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AStorageBox : public ABasicInteractiveActor
{
	GENERATED_BODY()
public:

	AStorageBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Storage")
		TArray<FItemDataStruct> StorageArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Storage")
		UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Storage")
		bool bOpen;

	virtual void BeginPlay() override;

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Interact_Implementation(APawn* InteractCauser) override;
};
