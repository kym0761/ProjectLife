// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueStruct.h"
#include "DialogueWidget.generated.h"

class UTextBlock;
class UButton;
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

	UPROPERTY( BlueprintReadWrite, Meta = (BindWidget))
		UButton* Button_Next;

	UPROPERTY( BlueprintReadWrite, Meta = (BindWidget))
		UButton* Button_End;

	//TextOffset
	UPROPERTY()
		int32 CurrentDialoguePos;

	FTimerHandle DialogueTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue", meta = (MinClamp = 0.01, MaxClamp = 1.0))
		float DialogueSpeed;

	UPROPERTY()
	TArray<FDialogueData> Dialogues;

	UPROPERTY()
		int32 CurrentDialogueNum;

	UPROPERTY()
	float DialogueTick;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void InitDialogueWidget(TArray<FDialogueData> InDialogues);

	UFUNCTION(BlueprintCallable)
		void StartDialogue();

	void SetNameText();
	void SetDialogueText();

	UFUNCTION()
		void DialogueFunction();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
