// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkEdge.h"
#include "NiagaraComponent.h"
#include "LinkComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "LinkHold.h"
#include "LinkTrigger.h"


// Sets default values
ALinkEdge::ALinkEdge()
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
void ALinkEdge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALinkEdge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetEffectPoint();

}

void ALinkEdge::InitializeCompRefs(ULinkComponent* InComp1, ULinkComponent* InComp2)
{
	if (IsValid(InComp1) && IsValid(InComp2))
	{
		LinkComps.Add(InComp1);
		LinkComps.Add(InComp2);
	}
}


void ALinkEdge::SetEffectPoint()
{
	//연결 Effect의 포인트를 설정해주어야함. ULinkComponent가 USceneComponent이므로 X Y Z 값이 존재함.

	if (LinkComps.IsValidIndex(0) && LinkComps.IsValidIndex(1))
	{
		LinkEffectComponent->SetNiagaraVariableVec3(TEXT("StartPoint"), LinkComps[0]->GetComponentLocation());
		LinkEffectComponent->SetNiagaraVariableVec3(TEXT("EndPoint"), LinkComps[1]->GetComponentLocation());
	}
}

