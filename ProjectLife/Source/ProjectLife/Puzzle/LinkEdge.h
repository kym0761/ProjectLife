// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinkEdge.generated.h"

class UNiagaraComponent;
class ULinkComponent;
class USceneComponent;

UCLASS()
class PROJECTLIFE_API ALinkEdge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALinkEdge();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<USceneComponent> DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UNiagaraComponent> LinkEffectComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ref")
		TArray<TObjectPtr<ULinkComponent>> LinkComps;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Should Call when Spawn.
	void InitializeCompRefs(ULinkComponent* InComp1, ULinkComponent* InComp2);
	void SetEffectPoint();

};
