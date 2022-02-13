// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConversationStruct.h"
#include "ConversationWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UConversationWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_NameText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_ConversationText;

	UPROPERTY( BlueprintReadWrite, Meta = (BindWidget))
		UButton* Button_Next;

	UPROPERTY( BlueprintReadWrite, Meta = (BindWidget))
		UButton* Button_End;

	//TextOffset
	UPROPERTY()
		int32 CurrentConversationPos;

	//FTimerHandle DialogueTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue", meta = (MinClamp = 0.01, MaxClamp = 1.0))
		float ConversationSpeed;

	UPROPERTY()
	TArray<FConversationData> Conversations;

	UPROPERTY()
		int32 CurrentConversationNum;

	UPROPERTY()
	float ConversationTick;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void InitConversationWidget(TArray<FConversationData> InConversations);

	UFUNCTION(BlueprintCallable)
		void StartConversation();

	void SetNameText();
	void SetConversationText();

	UFUNCTION()
		void ConversationFunction();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
