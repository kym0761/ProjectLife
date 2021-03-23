// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionIconBase.h"
#include "Components/Image.h"
#include "Ability.h"
#include "Buff.h"
#include "DeBuff.h"
void UConditionIconBase::NativeConstruct()
{
	Super::NativeConstruct();

}

void UConditionIconBase::InitIcon(AAbility* ConditionActorRef)
{
	ABuff* buff = Cast<ABuff>(ConditionActorRef);
	ADeBuff* deBuff = Cast<ADeBuff>(ConditionActorRef);

	if (ConditionImage)
	{
		if (buff)
		{
			ConditionRef = buff;
			if (buff->BuffData.Thumbnail)
			{
				ConditionImage->SetBrushFromTexture(buff->BuffData.Thumbnail);
			}
		}
		else if (deBuff)
		{
			ConditionRef = deBuff;
			if (deBuff->DeBuffData.Thumbnail)
			{
				ConditionImage->SetBrushFromTexture(deBuff->DeBuffData.Thumbnail);
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(5, 5.0f, FColor::Silver, TEXT("Casting in Condition Icon Failed"));
			}
		}
	}
}
