// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "GamePlay/ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
void UQuestViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UQuestViewWidget::InitializeWidget()
{
	if (GetWorld())
	{
		GameInstanceRef = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (IsValid(GameInstanceRef))
		{

		}

	}
}

bool UQuestViewWidget::Initialize()
{
	bool succeed = Super::Initialize();

	if (!succeed)
	{
		return false;
	}

	InitializeWidget();

	return true;
}
