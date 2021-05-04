// Fill out your copyright notice in the Description page of Project Settings.


#include "Chicken.h"
#include "LivestockProduceComponent.h"
AChicken::AChicken()
{
	LivestockProduceComponent = CreateDefaultSubobject<ULivestockProduceComponent>(TEXT("LivestockProduceComponent"));

}
