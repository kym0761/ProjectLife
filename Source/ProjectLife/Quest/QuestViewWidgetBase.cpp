// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestViewWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
void UQuestViewWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidget();

}

void UQuestViewWidgetBase::InitializeWidget()
{
	if (GetWorld())
	{
		GameInstanceRef = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}
}
