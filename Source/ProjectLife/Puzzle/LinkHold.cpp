// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkHold.h"
#include "LinkComponent.h"

ALinkHold::ALinkHold()
{
	LinkComponent = CreateDefaultSubobject<ULinkComponent>(TEXT("LinkComponent"));
	LinkComponent->SetupAttachment(RootComponent);
}
