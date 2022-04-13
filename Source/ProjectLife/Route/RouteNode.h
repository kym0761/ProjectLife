// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RouteNode.generated.h"

UCLASS()
class PROJECTLIFE_API ARouteNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARouteNode();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Route")
	//	TArray<ARouteNode*> NearNodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Route")
		FString NodeName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UCLASS(BlueprintType)
class URouteInfo : public UObject
{
	GENERATED_BODY()

public:

	URouteInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float G;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ARouteNode* RouteNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		URouteInfo* RouteParentInfo;
};