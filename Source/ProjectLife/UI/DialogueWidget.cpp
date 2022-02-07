// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DialogueSpeed = 0.1f;
}

void UDialogueWidget::SetNameText(FString InData)
{
	if (IsValid(TextBlock_Name))
	{
		TextBlock_Name->SetText(FText::FromString(InData));
	}
}

void UDialogueWidget::SetDialogueText(FString InData)
{
	if (IsValid(TextBlock_Dialogue))
	{
		//텍스트가 바뀔 때 초기화
		CurrentDialoguePos = 0;
		//UI 블루프린트에 존재하는 임시 텍스트 삭제
		TextBlock_Dialogue->SetText(FText());


		FTimerDelegate dialogueDelegate = FTimerDelegate::CreateUObject(this, &UDialogueWidget::DialogueFunction, InData);
		GetWorld()->GetTimerManager().SetTimer(DialogueTimer, dialogueDelegate, DialogueSpeed, true);
	}
}

void UDialogueWidget::DialogueFunction(FString InData)
{
	//타이머 작동마다 보여주는 텍스트 1씩 증가시켜서 대화하는 느낌이 나도록 함.
	CurrentDialoguePos = FMath::Clamp(CurrentDialoguePos + 1, 0, InData.Len());
	FString substring = UKismetStringLibrary::GetSubstring(InData, 0, CurrentDialoguePos);
	TextBlock_Dialogue->SetText(FText::FromString(substring));

	//대화가 전부 끝나면 타이머를 종료하여 더이상 타이머가 동작하지 않도록 함.
	if (CurrentDialoguePos == InData.Len())
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimer);
	}

}

void UDialogueWidget::TestDialogue()
{
	FString testString = FString("aaaa\nbbbb\nccccc");
	SetDialogueText(testString);
}
