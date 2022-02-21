// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/VerticalBox.h"
#include "ChoiceSlot.h"

void UConversationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConversationSpeed = 0.1f;

	CurrentConversationPos = 0;
	CurrentConversationNum = 0;
	CurrentConversationDataTableNum = 0;
	CurrentChoiceDataTableNum = 0;

}

void UConversationWidget::InitConversationWidget(TArray<UDataTable*> InConversations)
{
	ConversationDataTable = InConversations;

	InitConversation();

	StartConversation();
}

void UConversationWidget::InitConversationWidget_Choice(TArray<UDataTable*> InChoices)
{
	ChoiceDataTable = InChoices;
}

void UConversationWidget::InitConversation()
{
	//Init All
	Conversations.Empty();
	Button_Next->SetVisibility(ESlateVisibility::Visible);
	CurrentConversationNum = -1;
	CurrentConversationPos = 0;
	VerticalBox_Choices->ClearChildren();

	//Set First Conversation
	TArray<FConversationData*> data;
	ConversationDataTable[CurrentConversationDataTableNum]->GetAllRows<FConversationData>("", data);
	for (int i = 0; i < data.Num(); i++)
	{
		Conversations.Add(*data[i]);
	}

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
	if (CurrentConversationNum>= Conversations.Num() - 1)
	{
		Button_Next->SetVisibility(ESlateVisibility::Hidden);

		//선택지가 있다면 보여준다.
		if (ChoiceDataTable.IsValidIndex(CurrentChoiceDataTableNum))
		{
			TArray<FConversationChoiceData*> data;
			ChoiceDataTable[CurrentChoiceDataTableNum]->GetAllRows<FConversationChoiceData>("", data);
			//갯수만큼 생성함.
			for (int i = 0; i < data.Num(); i++)
			{
				UChoiceSlot* slot = NewObject<UChoiceSlot>(GetOwningPlayer(),ChoiceSlot_BP);
				if (IsValid(slot))
				{
					slot->AddToViewport();
					slot->InitChoiceSlot(this,*data[i], i + 1);
					VerticalBox_Choices->AddChild(slot);
					UE_LOG(LogTemp, Warning, TEXT("Slot Add OK"));
				}
			}			
		}
	}

	//이름 , 대화 내용 적용
	SetNameText();
	SetConversationText();
	
	//TODO : 캐릭터 이미지를 대화창에 적용이 필요함.

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

void UConversationWidget::ReceiveChoice(int32 ChoiceNumber)
{

	if (ChoiceNumber <= 0)
	{
		//Error.
		return;
	}

	//TODO : 전달받은 선택지 번호에 따라 다음 대화들을 함.
	CurrentConversationDataTableNum += ChoiceNumber;
	CurrentChoiceDataTableNum++;

	InitConversation();
	StartConversation();
}
