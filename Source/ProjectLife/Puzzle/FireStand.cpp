// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStand.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "ButtonTrigger.h"
#include "NiagaraComponent.h"
#include "FireTimerWidget.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"


AFireStand::AFireStand()
{
	PrimaryActorTick.bCanEverTick = true;

	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	SetRootComponent(Stand);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetVisibility(false);
	Widget->SetHiddenInGame(true);
	Widget->SetupAttachment(Stand);

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(Stand, TEXT("EffectSocket"));
	FireEffect->bAutoActivate = false;

	FireOverlap = CreateDefaultSubobject<UBoxComponent>(TEXT("FireOverlap"));
	FireOverlap->InitBoxExtent(FVector(48.0f, 48.0f, 100.0f));
	FireOverlap->SetRelativeLocation(FVector(0.0f,0.0f, 80.0f));
	FireOverlap->SetupAttachment(RootComponent);

	bUseTimer = false;
	bOffImmediately = false;
	TriggerWaitTime = 2.5f;
	CurrentTime = 0.0f;

	TimerInRate = 0.1f;
	TimerFirstDelay = 0.5f;
}

void AFireStand::BeginPlay()
{
	Super::BeginPlay();

	//Set Default Timer Widget Object
	if (IsValid(Widget))
	{
		UFireTimerWidget* fireWidget = Cast<UFireTimerWidget>(Widget->GetUserWidgetObject());
		if (fireWidget)
		{
			fireWidget->FireRef = this;
		}
	}
}

void AFireStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//use Timer
	if (bUseTimer && bTriggerActive)
	{
		CurrentTime = FMath::Clamp(CurrentTime - DeltaTime, 0.0f, TriggerWaitTime);

		if (CurrentTime <= 0)
		{
			TurnOffFire();
		}
	}
}

void AFireStand::TriggerAction_Implementation()
{
	bool bReady = true;

	//Check All Allocated Trigger are Activated.
	for (APuzzleTrigger* i : TriggerArray)
	{
		if (i->bTriggerActive == false)
		{
			bReady = false;
			break;
		}
	}

	if (bReady)
	{
		TurnOnFire();
	}
	else if (bOffImmediately && bTriggerActive && !bReady) // if This Fire Need To Off Immediately, and not Ready, will Turn off the Fire.
	{
		TurnOffFire();
	}
}

void AFireStand::Reset_Implementation()
{

	//Reset Fire Effect And TimerWidget.

	bTriggerActive = false;
	FireEffect->DeactivateImmediate();

	if (ResetNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ResetNiagaraSystem, GetActorLocation());
	}

	if (bUseTimer)
	{
		CurrentTime = 0.0f;
		Widget->SetVisibility(false);
		Widget->SetHiddenInGame(true);
	}

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Red, TEXT("Fire is reset!"));
	//}
}

void AFireStand::Combust_Implementation()
{
	TurnOnFire();
}

void AFireStand::TurnOnFire()
{
	bTriggerActive = true;

	if (!FireEffect->IsActive())
	{
		FireEffect->Activate();
	}

	if (bUseTimer)
	{
		CurrentTime = TriggerWaitTime;
		
		if (!Widget->IsVisible())
		{
			Widget->SetVisibility(true);
		}

		if (Widget->bHiddenInGame)
		{
			Widget->SetHiddenInGame(false);
		}
		
	}

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Red, TEXT("Fire is Activated!"));
	//}

	//Trigger All things that must Trigger.
	for (AActor* i : TriggeringArray)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UTriggerable::StaticClass());
		if (bInterfaceValid)
		{
			ITriggerable::Execute_TriggerAction(i);
		}
	}

	//Combust Timer On
	if (!CombustTimer.IsValid()) // Do Once. Check is Valid or not
	{
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireStand::OverlapCombust, TimerInRate, true, TimerFirstDelay);
	}
}

void AFireStand::TurnOffFire()
{
	bTriggerActive = false;
	if (FireEffect->IsActive())
	{
		FireEffect->Deactivate();
	}

	if (bUseTimer)
	{
		if (Widget->IsVisible())
		{
			Widget->SetVisibility(false);
		}

		if (!Widget->bHiddenInGame)
		{
			Widget->SetHiddenInGame(true);
		}
	}


	//Notify that It Won't Activate.
	for (AActor* i : TriggeringArray)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UTriggerable::StaticClass());
		if (bInterfaceValid)
		{
			ITriggerable::Execute_TriggerAction(i);
		}
	}

	//Combust Timer Off
	if (CombustTimer.IsValid())// Do Once. Check is Valid or not
	{
		GetWorldTimerManager().ClearTimer(CombustTimer);
	}

}

void AFireStand::OverlapCombust()
{
	if (bTriggerActive)
	{
		TArray<AActor*> overlapActors;

		FireOverlap->GetOverlappingActors(overlapActors);
		overlapActors.Remove(this);
		//UE_LOG(LogTemp, Warning, TEXT("%d"), overlapActors.Num());

		for (AActor* i : overlapActors)
		{
			bool bInterfaceValid = i->GetClass()->ImplementsInterface(UCombustible::StaticClass());
			if (bInterfaceValid)
			{
				ICombustible::Execute_Combust(i);

				//if (GEngine)
				//{
				//	FString temp = FString("Combust! Call OverlapCombust()! ---> combusted Actor Name : ") + i->GetName();
				//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Red, temp);
				//}

			}
		}
	}


}