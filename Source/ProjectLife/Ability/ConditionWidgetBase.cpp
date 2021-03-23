// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionWidgetBase.h"
#include "Components/HorizontalBox.h"
#include "ConditionIconBase.h"

void UConditionWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();


}

void UConditionWidgetBase::AddIcon(AAbility* ConditionActorRef)
{
	if (ConditionBox && ConditionIconClass)
	{
		UConditionIconBase* ConditionIcon = CreateWidget<UConditionIconBase>(this, ConditionIconClass);
		
		if (ConditionIcon)
		{
			ConditionBox->AddChild(ConditionIcon);

			ConditionIcon->InitIcon(ConditionActorRef);
		}
	}
}

void UConditionWidgetBase::RemoveIcon(AAbility* ConditionActorRef)
{

	for (int32 i = 0; i < ConditionBox->GetChildrenCount(); i++)
	{
		UConditionIconBase* child = Cast<UConditionIconBase>(ConditionBox->GetChildAt(i));
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
