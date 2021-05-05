// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
//#include "Components/SphereComponent.h"
#include "LinkComponent.generated.h"

class ALinkEdgeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API ULinkComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULinkComponent();

	//If This Set, Always Activate.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Link")
		bool bRootLink;

	//Current Link's Edges
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		TArray<ALinkEdgeBase*> LinkEdges;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		float MaxDistance;

	//Edge Spawn Class.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
		TSubclassOf<ALinkEdgeBase> LinkEdgeClass;

	//Other LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		TArray<ULinkComponent*> LinkComps;

	//Adjacent LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		TArray<ULinkComponent*> AdjacentLinkComps;

	FTimerHandle LinkTimer;

	const float LinkJobInterval = 0.05f;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		bool bLinkActivated;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetLinkActivate() const;
	void SetLinkActivate(bool InVal);

	bool CheckLinkedWithRoot();

	bool CheckEdgeCanExist(ULinkComponent* OtherLinkComp);
	bool CheckCompDistance(ULinkComponent* OtherLinkComp);

	void TrySpawnEdge(ULinkComponent* OtherLinkComp);
	void TryRemoveEdge(ULinkComponent* OtherLinkComp);
	void TryRemoveAllEdges();

	//Will Called in BeginPlay()
	void FindAllOtherLinkComps();

	void ReEvaluateAllLinks();

	//Called In Timer.
	UFUNCTION()
	void LinkJob();
};
