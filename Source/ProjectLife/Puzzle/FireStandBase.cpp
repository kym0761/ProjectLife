// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStandBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "ButtonTriggerBase.h"
#include "NiagaraComponent.h"
#include "FireTimerWidgetBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"


AFireStandBase::AFireStandBase()
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

void AFireStandBase::BeginPlay()
{
	Super::BeginPlay();

	//Set Default Timer Widget Object
	if (IsValid(Widget))
	{
		UFireTimerWidgetBase* fireWidget = Cast<UFireTimerWidgetBase>(Widget->GetUserWidgetObject());
		if (fireWidget)
		{
			fireWidget->FireRef = this;
		}
	}
}

void AFireStandBase::Tick(float DeltaTime)
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

void AFireStandBase::TriggerAction_Implementation()
{
	bool bReady = true;

	//Check All Allocated Trigger are Activated.
	for (APuzzleTriggerBase* i : TriggerArray)
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

void AFireStandBase::Reset_Implementation()
{
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

void AFireStandBase::Combust_Implementation()
{
	TurnOnFire();
}

void AFireStandBase::TurnOnFire()
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
		GetWorldTimerManager().SetTimer(CombustTimer, this, &AFireStandBase::OverlapCombust, TimerInRate, true, TimerFirstDelay);
	}
}

void AFireStandBase::TurnOffFire()
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

//void AFireStandBase::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//	
//	if (bTriggerActive)
//	{
//		bool bInterfaceValid = OtherActor->GetClass()->ImplementsInterface(UCombustible::StaticClass());
//
//		if (bInterfaceValid)
//		{
//			ICombustible::Execute_Combust(OtherActor);
//
//			if (GEngine)
//			{
//				FString temp = FString("Combust! --->") + OtherActor->GetName();
//				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Red, temp);
//			}
//		}
//	}
//}

void AFireStandBase::OverlapCombust()
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
