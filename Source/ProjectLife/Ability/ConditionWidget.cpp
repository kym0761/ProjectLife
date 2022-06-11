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
	//추가된 Ability의 아이콘을 추가
	if (IsValid(ConditionBox) && IsValid(ConditionIconClass))
	{
		UConditionIconWidget* ConditionIcon = CreateWidget<UConditionIconWidget>(this, ConditionIconClass);

		if (IsValid(ConditionIcon))
		{
			ConditionBox->AddChild(ConditionIcon);

			ConditionIcon->InitIcon(ConditionActorRef);
		}
	}
}

void UConditionWidget::RemoveIcon(AAbility* ConditionActorRef)
{
	//삭제된 Ability의 아이콘을 삭제
	for (int32 i = 0; i < ConditionBox->GetChildrenCount(); i++)
	{
		UConditionIconWidget* child = Cast<UConditionIconWidget>(ConditionBox->GetChildAt(i));
		if (IsValid(child))
		{
			if (child->GetConditionRef() == ConditionActorRef)
			{
				ConditionBox->RemoveChildAt(i);
				child->RemoveFromParent();
			}
		}
	}
}
