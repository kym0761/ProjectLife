// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"
#include "AbilityComponent.h"
// Sets default values
AAbility::AAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(false);
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();

	GetActorNameOrLabel();
}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility::SetAbilityOwner(AActor* Value)
{
	if (IsValid(Value))
	{
		AbilityOwner = Value;
	}
}

void AAbility::StartAbility()
{
	//Ability가 처음 시작할 떄
	//Owner의 AbilityComponent에 ability를 등록함.
	if (IsValid(AbilityOwner))
	{
		UAbilityComponent* abilityComponent = AbilityOwner->FindComponentByClass<UAbilityComponent>();

		if (IsValid(abilityComponent))
		{
			abilityComponent->AddAbility(this);
		}
	}

	//액티브 효과 발동
	ActivateActiveEffect();

	//패시브 효과도 발동
	ActivatePassiveEffect();
	
	//지속시간이 존재한다면, 타이머도 동작함.
	switch (AbilityData.AbilityDurabilityType)
	{
	case EAbilityDurabilityType::Once:
		DestroyAbilityWithEndEffect();
		break;
	case EAbilityDurabilityType::Limited:
		CurrentDurationTime = AbilityData.Duration;
		//Timer setting for End
		GetWorldTimerManager().SetTimer(AbilityCountdownTimer, this, &AAbility::AbilityEndTimerFunction, 1.0f, true, 1.0f);
		break;
	case EAbilityDurabilityType::Infinite:
		//Do Nothing.
		break;
	default:
		break;
	}

}

void AAbility::ActivateActiveEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivateActiveEffect.. Please Override it."));
	}
}

void AAbility::ActivatePassiveEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivatePassive.. Please Override it."));
	}
}

void AAbility::EndAbility_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("EndAbility.. Please Override it."));
	}
}

void AAbility::ActivateEndEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivateEndEffect.. Please Override it."));
	}
}

void AAbility::DestroyAbilityWithoutEndEffect()
{
	//강제로 종료 당했을 때 발동되어야함.
	//예시) 보호막이 부셔졌을 때 후폭풍 효과가 없어야함.
	
	//타이머 종료
	if (GetWorldTimerManager().IsTimerActive(AbilityCountdownTimer))
	{
		AbilityCountdownTimer.Invalidate();
		GetWorldTimerManager().ClearTimer(AbilityCountdownTimer);
	}

	//끝날 때 효과 없이 Destroy
	Destroy();
}

void AAbility::DestroyAbilityWithEndEffect()
{
	//지속시간이 다 되었을 때 발동되어야함.
	//예시) 보호막이 지속시간까지 유지되었을 때 후폭풍 효과가 있어야함.

	//타이머 종료
	if (GetWorldTimerManager().IsTimerActive(AbilityCountdownTimer))
	{
		AbilityCountdownTimer.Invalidate();
		GetWorldTimerManager().ClearTimer(AbilityCountdownTimer);
	}

	//끝날 때 효과 발동한 뒤에 Destroy.
	ActivateEndEffect();
	Destroy();
}

void AAbility::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(AbilityOwner))
	{
		//어빌리티 컴포넌트에 해당 어빌리티가 종료되어 삭제됨을 알려야함.
		//아직 구현 안했으니까 지금 건드릴 필요 없음.
		UAbilityComponent* abilityComponent = AbilityOwner->FindComponentByClass<UAbilityComponent>();
		if (IsValid(abilityComponent))
		{
			abilityComponent->RemoveAbility(this);
		}

		EndAbility();
	}
}

void AAbility::AbilityEndTimerFunction()
{
	//BeginPlay에 있는 타이머 설정에 의해
	//1초 단위로 지속시간이 1씩 까인다.
	//지속시간이 끝나면 정상적으로 종료함.
	if (CurrentDurationTime <= 0.0f)
	{
		CurrentDurationTime = 0.0f;
		DestroyAbilityWithEndEffect();
	}
	//else
	//{
	//	if (GEngine)
	//	{
	//		FString str = TEXT("currentTime : ")
	//			+ FString::SanitizeFloat(CurrentDurationTime);

	//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
	//	}
	//}

	CurrentDurationTime = FMath::Clamp(CurrentDurationTime - 1.0f, 0.0f, AbilityData.Duration);
}

