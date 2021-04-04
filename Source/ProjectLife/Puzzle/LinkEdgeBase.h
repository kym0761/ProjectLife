// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "LinkEdgeBase.generated.h"

class UNiagaraComponent;
class ULinkComponent;
class USceneComponent;


///**
// * Class for Edge Array.
// */
//UCLASS(BlueprintType, Blueprintable)
//class PROJECTLIFE_API ULinkEdges : public UObject
//{
//	GENERATED_BODY()
//
//public:
//
//	ULinkEdges();
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edge")
//		TArray<ALinkEdgeBase*> LinkEdges;
//
//};


UCLASS()
class PROJECTLIFE_API ALinkEdgeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALinkEdgeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UNiagaraComponent* LinkEffectComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ref")
		TArray<ULinkComponent*> LinkComps;

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
