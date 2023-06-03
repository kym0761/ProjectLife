// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestViewWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UButton;
class UScrollBox;
class UProjectLIfeGameInstance;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UQuestViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UTextBlock> QuestNameText;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UTextBlock> QuestDescriptionText;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UVerticalBox> QuestObjectivesBox;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UVerticalBox> QuestRewardsBox;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UButton> CurrentQuestButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UButton> CompletedQuestButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UButton> ExitButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		TObjectPtr<UScrollBox> QuestScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
		TObjectPtr<UProjectLIfeGameInstance> GameInstanceRef;

	virtual void NativeConstruct() override;

	void InitializeWidget();

protected:

	virtual bool Initialize() override;

};
