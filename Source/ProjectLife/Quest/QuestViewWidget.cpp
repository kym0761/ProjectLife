// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
void UQuestViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidget();

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
