// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetStringLibrary.h"

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConversationSpeed = 0.1f;
}

void UConversationWidget::InitConversationWidget(TArray<FConversationData> InConversations)
{
	Conversations = InConversations;
	CurrentConversationNum = -1;
	//DialogueSeqNum = 0;

	StartConversation();
}

void UConversationWidget::StartConversation()
{
	if (CurrentConversationNum >= Conversations.Num() - 1)
	{
		// ��ȭ ��Ȱ��ȭ
		return;
	}

	CurrentConversationNum++;

	//������ ��ȭ���, ���� ��ȭ ��ư�� ������.
	if (CurrentConversationNum >= Conversations.Num() - 1)
	{
		Button_Next->SetVisibility(ESlateVisibility::Hidden);
	}

	//�̸� , ��ȭ ���� ����
	SetNameText();
	SetConversationText();
	
	//TODO : ĳ���� �̹��� ����?

}

void UConversationWidget::SetNameText()
{
	if (IsValid(TextBlock_NameText))
	{
		TextBlock_NameText->SetText(FText::FromString(Conversations[CurrentConversationNum].Name));
	}
}

void UConversationWidget::SetConversationText()
{
	if (IsValid(TextBlock_ConversationText))
	{
		//�ؽ�Ʈ�� �ٲ� �� �ʱ�ȭ
		CurrentConversationPos = 0;
		//UI �������Ʈ�� �����ϴ� �ӽ� �ؽ�Ʈ ����
		TextBlock_ConversationText->SetText(FText());

		ConversationFunction();
	}
}

void UConversationWidget::ConversationFunction()
{
	FString conversationText = Conversations[CurrentConversationNum].ConversationText;

	if (conversationText.Len() <= CurrentConversationPos)
	{
		return;
	}

	//�۵����� �����ִ� �ؽ�Ʈ 1�� �������Ѽ� ��ȭ�ϴ� ������ ������ ��.
	CurrentConversationPos = FMath::Clamp(CurrentConversationPos + 1, 0, conversationText.Len());
	FString substring = UKismetStringLibrary::GetSubstring(conversationText, 0, CurrentConversationPos);
	TextBlock_ConversationText->SetText(FText::FromString(substring));

}

void UConversationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ConversationTick += InDeltaTime;

	//�ð��� ������ ������ ���� �ؽ�Ʈ�� ��µǵ��� ��.
	//����) �� / �ȳ� / �ȳ��� / �ȳ��ϼ� / �ȳ��ϼ���
	//Timer�� ������ Pause�Ǹ� ���߹Ƿ� UI�� Tick�� �̿��� ������.
	if (ConversationTick >= ConversationSpeed)
	{
		ConversationTick = 0.0f;
		ConversationFunction();
	}

}
