// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "LinkComponent.generated.h"

class ALinkEdge;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API ULinkComponent : public UCapsuleComponent
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
		TArray<ALinkEdge*> LinkEdges;

	//Edge Spawn Class.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
		TSubclassOf<ALinkEdge> LinkEdgeClass;

	//Other LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		TArray<ULinkComponent*> LinkComps;

	//Adjacent LinkComponents.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Link")
		TArray<ULinkComponent*> AdjacentLinkComps;

	FTimerHandle LinkTimer;

private:

	const float LinkJobInterval = 0.03f;

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

	void TrySpawnEdge(ULinkComponent* OtherLinkComp);
	void TryRemoveEdge(ULinkComponent* OtherLinkComp);
	void TryRemoveAllEdges();

	//Will Called in BeginPlay()
	void FindAllOtherLinkComps();

	void ReEvaluateAllLinks();

	//Called In Timer.
	UFUNCTION()
	void LinkJob();


	/*BeginOverlap will not Need. Because, Overlap check is needed periodically. so Overlap Will Active cyclically*/
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
