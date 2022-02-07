// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Name;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Dialogue;

	UPROPERTY()
		int32 CurrentDialoguePos;

	FTimerHandle DialogueTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (MinClamp=0.01,MaxClamp=1.0))
		float DialogueSpeed;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetNameText(FString InData);
	UFUNCTION(BlueprintCallable)
	void SetDialogueText(FString InData);

	UFUNCTION()
		void DialogueFunction(FString InData);

	//temporal Test Function.
	UFUNCTION(BlueprintCallable)
		void TestDialogue();
};
