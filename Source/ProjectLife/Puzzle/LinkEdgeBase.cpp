// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkEdgeBase.h"
#include "NiagaraComponent.h"
#include "LinkComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "LinkHoldBase.h"
#include "LinkTriggerBase.h"


// Sets default values
ALinkEdgeBase::ALinkEdgeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	LinkEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LinkEffectComponent"));
	LinkEffectComponent->SetupAttachment(RootComponent);
	LinkEffectComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void ALinkEdgeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALinkEdgeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetEffectPoint();

}

void ALinkEdgeBase::InitializeCompRefs(ULinkComponent* InComp1, ULinkComponent* InComp2)
{
	if (IsValid(InComp1) && IsValid(InComp2))
	{
		LinkComps.Add(InComp1);
		LinkComps.Add(InComp2);
	}
}


void ALinkEdgeBase::SetEffectPoint()
{
	if (LinkComps.IsValidIndex(0) && LinkComps.IsValidIndex(1))
	{
		LinkEffectComponent->SetNiagaraVariableVec3(TEXT("StartPoint"), LinkComps[0]->GetComponentLocation());
		LinkEffectComponent->SetNiagaraVariableVec3(TEXT("EndPoint"), LinkComps[1]->GetComponentLocation());
	}
}

