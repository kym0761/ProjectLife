// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractNotifyWidgetBase.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UInteractNotifyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NameTextBlock;

	UPROPERTY()
	AActor* ActorRef;

	virtual void NativeConstruct() override;

	void NotifyInteract(AActor* InActor);
	void UnnotifyInteract();

};
