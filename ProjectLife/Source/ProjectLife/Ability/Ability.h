// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityStruct.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS()
class PROJECTLIFE_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
		FAbilityDataStruct AbilityData;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
		float CurrentDurationTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<AActor> AbilityOwner;

	//어빌리티 당 Target은 단 한명 -> 예시) 독 장판이 여러 명에게 각각 중독 어빌리티를 뿌림
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<AActor> AbilityTarget;

	FTimerHandle AbilityCountdownTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//temp to set owner in blueprint test
	UFUNCTION(BlueprintCallable)
	void SetAbilityOwner(AActor* Value);

	//어빌리티의 시작 구현 부분. 현재 테스트를 위해서 blueprintcallable 상태
	UFUNCTION(BlueprintCallable)
	void StartAbility();

	/*어빌리티의 ActiveEffect, PassiveEffect, End , EndEfect는 블루프린트에서 구현되도록 함.*/
#pragma region Effect
	
	/*	어빌리티 처음에 발동할 효과를 지정
	*	예시 : 처음 발동시 주위 적에게 데미지를 줌.
	*/
	UFUNCTION(BlueprintNativeEvent)
	void ActivateActiveEffect();
	virtual void ActivateActiveEffect_Implementation();

	/*	어빌리티의 패시브 효과를 지정
	*	예시 : 어빌리티가 있는 동안 스탯 업?
	*/
	UFUNCTION(BlueprintNativeEvent)
	void ActivatePassiveEffect();
	virtual void ActivatePassiveEffect_Implementation();

	/*	Actor가 Destroy될 때 EndPlay()에서 발동함.
	*	예시 : 어빌리티가 종료되면 스탯 업 등의 효과를 제거함
	*/
	UFUNCTION(BlueprintNativeEvent)
	void EndAbility();
	virtual void EndAbility_Implementation();

	/*	어빌리티가 종료될 때 발동할 효과를 지정
	*	예시 : 어빌리티가 종료될 때 주위 적에게 데미지를 줌.
	*/
	UFUNCTION(BlueprintNativeEvent)
	void ActivateEndEffect();
	virtual void ActivateEndEffect_Implementation();
#pragma endregion

	//디스펠 당했거나, 올바르지 않게 효과가 종료될 때 발동
	UFUNCTION(BlueprintCallable)
	void DestroyAbilityWithoutEndEffect();
	
	//정상적으로 종료될 때 발동.
	UFUNCTION(BlueprintCallable)
	void DestroyAbilityWithEndEffect();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void AbilityEndTimerFunction();
};
