// Fill out your copyright notice in the Description page of Project Settings.


#include "Cow.h"
#include "MilkComponent.h"
ACow::ACow()
{
	MilkComponent = CreateDefaultSubobject<UMilkComponent>(TEXT("MilkComponent"));
}
