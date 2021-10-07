// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionWidget.h"
#include "Components/HorizontalBox.h"
#include "ConditionIconWidget.h"

void UConditionWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UConditionWidget::AddIcon(AAbility* ConditionActorRef)
{
	if (ConditionBox && ConditionIconClass)
	{
		UConditionIconWidget* ConditionIcon = CreateWidget<UConditionIconWidget>(this, ConditionIconClass);
		
		if (ConditionIcon)
		{
			ConditionBox->AddChild(ConditionIcon);

			ConditionIcon->InitIcon(ConditionActorRef);
		}
	}
}

void UConditionWidget::RemoveIcon(AAbility* ConditionActorRef)
{

	for (int32 i = 0; i < ConditionBox->GetChildrenCount(); i++)
	{
		UConditionIconWidget* child = Cast<UConditionIconWidget>(ConditionBox->GetChildAt(i));
		if (child)
		{
			if (child->ConditionRef == ConditionActorRef)
			{
				ConditionBox->RemoveChildAt(i);
				child->RemoveFromParent();
			}
		}
	}
}
