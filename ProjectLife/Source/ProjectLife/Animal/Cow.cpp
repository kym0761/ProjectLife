// Fill out your copyright notice in the Description page of Project Settings.


#include "Cow.h"
#include "LivestockProduceComponent.h"
ACow::ACow()
{
	LivestockProduceComponent = CreateDefaultSubobject<ULivestockProduceComponent>(TEXT("LivestockProduceComponent"));

}
