// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidgetBase.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UDamageTextWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

}

void UDamageTextWidgetBase::SetDamageText(float InDamage)
{
	if (DamageTextBlock)
	{
		FText temp = UKismetTextLibrary::Conv_FloatToText(InDamage, ERoundingMode::HalfToEven);
		DamageTextBlock->SetText(temp);
	}
}
