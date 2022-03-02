// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ConversationWidget.h"

FReply UChoiceSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

    if (!IsValid(ConversationWidgetRef))
    {
        //failed
        return FReply::Unhandled();
    }

    //선택지 정보를 넘겨줌
    ConversationWidgetRef->ReceiveChoice(ChoiceNum);
    UE_LOG(LogTemp, Warning, TEXT("ChoiceSlot NativeOnMouseButtonUp"));
    return FReply::Handled();
}

void UChoiceSlot::TestFunction()
{
    if (!IsValid(ConversationWidgetRef))
    {
        //failed
        return;
    }
    ConversationWidgetRef->ReceiveChoice(ChoiceNum);
}

void UChoiceSlot::InitChoiceSlot(UConversationWidget* ConversationWidget, FConversationChoiceData Indata, int32 Num)
{
    if (IsValid(TextBlock_ChoiceText))
    {
        TextBlock_ChoiceText->SetText(FText::FromString(Indata.ChoiceText));
    }
    
    ConversationWidgetRef = ConversationWidget;

    //Image_ChoiceIcon ;;;;;;

    ChoiceNum = Num;

}
