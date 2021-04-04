// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkHoldBase.h"
#include "LinkComponent.h"

ALinkHoldBase::ALinkHoldBase()
{
	LinkComponent = CreateDefaultSubobject<ULinkComponent>(TEXT("LinkComponent"));
	LinkComponent->SetupAttachment(RootComponent);
}
