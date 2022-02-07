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
		//�ؽ�Ʈ�� �ٲ� �� �ʱ�ȭ
		CurrentDialoguePos = 0;
		//UI �������Ʈ�� �����ϴ� �ӽ� �ؽ�Ʈ ����
		TextBlock_Dialogue->SetText(FText());


		FTimerDelegate dialogueDelegate = FTimerDelegate::CreateUObject(this, &UDialogueWidget::DialogueFunction, InData);
		GetWorld()->GetTimerManager().SetTimer(DialogueTimer, dialogueDelegate, DialogueSpeed, true);
	}
}

void UDialogueWidget::DialogueFunction(FString InData)
{
	//Ÿ�̸� �۵����� �����ִ� �ؽ�Ʈ 1�� �������Ѽ� ��ȭ�ϴ� ������ ������ ��.
	CurrentDialoguePos = FMath::Clamp(CurrentDialoguePos + 1, 0, InData.Len());
	FString substring = UKismetStringLibrary::GetSubstring(InData, 0, CurrentDialoguePos);
	TextBlock_Dialogue->SetText(FText::FromString(substring));

	//��ȭ�� ���� ������ Ÿ�̸Ӹ� �����Ͽ� ���̻� Ÿ�̸Ӱ� �������� �ʵ��� ��.
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
