// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConversationStruct.h"
#include "ChoiceSlot.generated.h"

class UConversationWidget;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UChoiceSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* TextBlock_ChoiceText;

	UPROPERTY(Meta = (BindWidget))
		UImage* Image_ChoiceIcon;

private:
	UPROPERTY()
		int32 ChoiceNum;

	UPROPERTY()
		UConversationWidget* ConversationWidgetRef;

public:

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	void TestFunction();

	void InitChoiceSlot(UConversationWidget* ConversationWidget, FConversationChoiceData Indata,int32 Num);

};
