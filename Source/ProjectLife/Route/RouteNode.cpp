// Fill out your copyright notice in the Description page of Project Settings.


#include "RouteNode.h"

// Sets default values
ARouteNode::ARouteNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARouteNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARouteNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

URouteInfo::URouteInfo()
{
	F = 0;
	G = 0;
	RouteNode = nullptr;
	RouteParentInfo = nullptr;
}
