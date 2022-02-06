// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractNotifyWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UInteractNotifyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NameTextBlock;

	//Interact 오브젝트는 여러가지가 존재하므로, UObject를 통해 확인.
	UPROPERTY()
		UObject* ObjectRef;

	virtual void NativeConstruct() override;

	void NotifyInteract(UObject* InObject);
	void UnnotifyInteract();

};
