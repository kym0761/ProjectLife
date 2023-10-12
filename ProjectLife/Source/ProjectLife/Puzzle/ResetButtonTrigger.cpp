// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetButtonTrigger.h"
#include "PuzzleInterfaces.h"
#include "Components/SphereComponent.h"

AResetButtonTrigger::AResetButtonTrigger()
{

}

void AResetButtonTrigger::BeginPlay()
{
	//APuzzleTrigger의 BeginPlay()는 Call되면 안됨.. 오직 AActor의 BeginPlay()만 호출되어야 함.
	//만약 APuzzleTrigger의 BeginPlay()이 호출되어 버리면, 리셋 버튼을 FromTrigger에 집어넣는 작업을 하게 됨
	//그렇게 된다면, 리셋 버튼이 눌리지 않는다면 TriggerAction이 작동하지 않게 될거임.
	//그런데, 리셋 버튼은 Reset 작업을 하게 되므로 작동이 서로 모순됨.
	Super::Super::Super::BeginPlay();

	InitializeForTimeline();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AResetButtonTrigger::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AResetButtonTrigger::OnButtonEndOverlap);
}

void AResetButtonTrigger::Tick(float DeltaTime)
{
	//ButtonTrigger를 보면 Tick()에 의해 Trigger() 가 지속적으로 동작하게 되어 있음
	// Reset Button은 Tick()에 의해 Trigger()가 지속적으로 작동되어야 할 이유가 없음.
	//Call AActor's Tick();
	Super::Super::Super::Tick(DeltaTime);

	TimelineHandle.TickTimeline(DeltaTime);
}

void AResetButtonTrigger::ButtonUp()
{
	// 기본 버튼의 Trigger()는 ButtonUp()에 의해 작동함. 리셋 버튼은 필요없으므로 해당 기능이 작동하지 않도록 오버라이드함.
	
	bTriggerActive = false;
	ButtonMeshUp();
}

void AResetButtonTrigger::Trigger()
{
	//find Resetable Actor and Do Reset.
	for (AActor* i : ToTrigger)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UResetable::StaticClass());
		if (bInterfaceValid)
		{
			IResetable::Execute_Reset(i);
		}
	}
}