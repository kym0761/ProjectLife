// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationStruct.h"

FConversationData::FConversationData()
{
	Emotion = EEmotionType::Normal;
	ConversationSpeed = 0.1f;
}

FConversationChoiceData::FConversationChoiceData()
{
	Emotion = EEmotionType::Normal;
}
