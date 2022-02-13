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
		// 대화 비활성화
		return;
	}

	CurrentConversationNum++;

	//마지막 대화라면, 다음 대화 버튼을 삭제함.
	if (CurrentConversationNum >= Conversations.Num() - 1)
	{
		Button_Next->SetVisibility(ESlateVisibility::Hidden);
	}

	//이름 , 대화 내용 적용
	SetNameText();
	SetConversationText();
	
	//TODO : 캐릭터 이미지 적용?

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
		//텍스트가 바뀔 때 초기화
		CurrentConversationPos = 0;
		//UI 블루프린트에 존재하는 임시 텍스트 삭제
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

	//작동마다 보여주는 텍스트 1씩 증가시켜서 대화하는 느낌이 나도록 함.
	CurrentConversationPos = FMath::Clamp(CurrentConversationPos + 1, 0, conversationText.Len());
	FString substring = UKismetStringLibrary::GetSubstring(conversationText, 0, CurrentConversationPos);
	TextBlock_ConversationText->SetText(FText::FromString(substring));

}

void UConversationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ConversationTick += InDeltaTime;

	//시간이 적절히 지나면 다음 텍스트가 출력되도록 함.
	//예시) 안 / 안녕 / 안녕하 / 안녕하세 / 안녕하세요
	//Timer는 게임의 Pause되면 멈추므로 UI의 Tick을 이용해 구현함.
	if (ConversationTick >= ConversationSpeed)
	{
		ConversationTick = 0.0f;
		ConversationFunction();
	}

}
