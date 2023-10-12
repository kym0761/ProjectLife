// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildingInfo.Generated.h"

USTRUCT(BlueprintType)
struct FBuildingInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SizeY;


	FBuildingInfo();

};