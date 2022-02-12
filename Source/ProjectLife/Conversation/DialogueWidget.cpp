// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetStringLibrary.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DialogueSpeed = 0.1f;
}

void UDialogueWidget::InitDialogueWidget(TArray<FDialogueData> InDialogues)
{
	Dialogues = InDialogues;
	CurrentDialogueNum = -1;
	//DialogueSeqNum = 0;

	StartDialogue();
}

void UDialogueWidget::StartDialogue()
{
	if (CurrentDialogueNum >= Dialogues.Num()-1)
	{
		//TODO : 대화 비활성화 필요함.
		return;
	}

	CurrentDialogueNum++;

	//마지막 대화면 다음 대화 버튼을 삭제함.
	if (CurrentDialogueNum >= Dialogues.Num() - 1)
	{
		Button_Next->SetVisibility(ESlateVisibility::Hidden);
	}

	//이름 , 대화 내용 적용
	SetNameText();
	SetDialogueText();
	
	//TODO : 캐릭터 이미지 적용?

}

void UDialogueWidget::SetNameText()
{
	if (IsValid(TextBlock_Name))
	{
		TextBlock_Name->SetText(FText::FromString(Dialogues[CurrentDialogueNum].Name));
	}
}

void UDialogueWidget::SetDialogueText()
{
	if (IsValid(TextBlock_Dialogue))
	{
		//텍스트가 바뀔 때 초기화
		CurrentDialoguePos = 0;
		//UI 블루프린트에 존재하는 임시 텍스트 삭제
		TextBlock_Dialogue->SetText(FText());

		DialogueFunction();
	}
}

void UDialogueWidget::DialogueFunction()
{
	FString dialogueText = Dialogues[CurrentDialogueNum].Dialogue;

	if (dialogueText.Len() <= CurrentDialoguePos)
	{
		return;
	}

	//타이머 작동마다 보여주는 텍스트 1씩 증가시켜서 대화하는 느낌이 나도록 함.
	CurrentDialoguePos = FMath::Clamp(CurrentDialoguePos + 1, 0, dialogueText.Len());
	FString substring = UKismetStringLibrary::GetSubstring(dialogueText, 0, CurrentDialoguePos);
	TextBlock_Dialogue->SetText(FText::FromString(substring));

}

void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DialogueTick += InDeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("NativeTick In DialogueWidget ---- %f"), DialogueTick);

	if (DialogueTick >= DialogueSpeed)
	{
		DialogueTick = 0.0f;
		DialogueFunction();
	}

}
