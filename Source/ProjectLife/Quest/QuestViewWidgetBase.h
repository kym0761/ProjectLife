// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestViewWidgetBase.generated.h"

class UTextBlock;
class UVerticalBox;
class UButton;
class UScrollBox;
class UProjectLIfeGameInstance;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UQuestViewWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* QuestNameText;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* QuestDescriptionText;
	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* QuestObjectivesBox;
	UPROPERTY(Meta = (BindWidget))
		UVerticalBox* QuestRewardsBox;
	UPROPERTY(Meta = (BindWidget))
		UButton* CurrentQuestButton;
	UPROPERTY(Meta = (BindWidget))
		UButton* CompletedQuestButton;
	UPROPERTY(Meta = (BindWidget))
		UButton* ExitButton;
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* QuestScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
		UProjectLIfeGameInstance* GameInstanceRef;

	virtual void NativeConstruct() override;

	void InitializeWidget();
};
