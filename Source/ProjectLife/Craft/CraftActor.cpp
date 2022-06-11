// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftActor.h"
#include "../Inventory/InventoryComponent.h"
#include "CraftComponent.h" 
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicPlayerController.h"
#include "CraftWidget.h"

// Sets default values
ACraftActor::ACraftActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	CraftComponent = CreateDefaultSubobject<UCraftComponent>(TEXT("CraftComponent"));
	bCanUse = true;

}

// Called when the game starts or when spawned
void ACraftActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACraftActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO : EndOverlap이 되면 사용중이던 CraftActor UI를 삭제하여 평소 플레이로 돌아갈 수 있게 함.
	//필요없게 된다면 굳이 안만들어도 됨.

	//기존에 있던 CraftWidget 제거
	if (IsValid(CraftWidgetRef))
	{
		CraftWidgetRef->RemoveFromViewport();
		CraftWidgetRef = nullptr;
	}
}

void ACraftActor::Interact_Implementation(APawn* InteractCauser)
{

	//Add To Viewport Storage UI.
	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();
	if (!IsValid(playerController))
	{
		//controller failed
		return;
	}

	//CraftWidget 생성 UI 블루프린트 연결 확인
	if (!IsValid(CraftWidgetClass))
	{
		return;
	}

	//기존에 있던 CraftWidget 제거
	if (IsValid(CraftWidgetRef))
	{
		CraftWidgetRef->RemoveFromViewport();
		CraftWidgetRef = nullptr;
	}

	//생성 및 초기화.
	CraftWidgetRef = CreateWidget<UCraftWidget>(playerController, CraftWidgetClass);
	if (!IsValid(CraftWidgetRef))
	{
		return;
	}
	CraftWidgetRef->AddToViewport();
	CraftWidgetRef->InitCraftWidget(this);

}

void ACraftActor::RequestCrafting(FString ItemNameToCraft)
{
	if (bCanUse == false)
	{
		//제작 중이므로 제작 요청을 받고 있으면 안됨.
		return;
	}

	if (!IsValid(CraftComponent))
	{
		return;
	}
	
	//CraftComponent에 의해 제작 가능 체크하고 제작에 들어감.
	bool bCanMake = CraftComponent->CheckCanMake(ItemNameToCraft);

	if (IsValid(InventoryComponent))
	{
		FItemSlotData temp = InventoryComponent->GetInventoryItem(10);
		if (!temp.IsEmpty())
		{
			return;
		}
	}

	if (bCanMake)
	{
		CraftComponent->StartCrafting(ItemNameToCraft, true, 10);
	}

}
