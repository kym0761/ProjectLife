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
		//TODO : ��ȭ ��Ȱ��ȭ �ʿ���.
		return;
	}

	CurrentDialogueNum++;

	//������ ��ȭ�� ���� ��ȭ ��ư�� ������.
	if (CurrentDialogueNum >= Dialogues.Num() - 1)
	{
		Button_Next->SetVisibility(ESlateVisibility::Hidden);
	}

	//�̸� , ��ȭ ���� ����
	SetNameText();
	SetDialogueText();
	
	//TODO : ĳ���� �̹��� ����?

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
		//�ؽ�Ʈ�� �ٲ� �� �ʱ�ȭ
		CurrentDialoguePos = 0;
		//UI �������Ʈ�� �����ϴ� �ӽ� �ؽ�Ʈ ����
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

	//Ÿ�̸� �۵����� �����ִ� �ؽ�Ʈ 1�� �������Ѽ� ��ȭ�ϴ� ������ ������ ��.
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
