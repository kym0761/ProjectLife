// Fill out your copyright notice in the Description page of Project Settings.


#include "RouteFindComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RouteNode.h"

// Sets default values for this component's properties
URouteFindComponent::URouteFindComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URouteFindComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URouteFindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ARouteNode* URouteFindComponent::FindNearestRouteNode()
{
	AActor* owner = GetOwner();

	if (!IsValid(owner))
	{
		//Failed
		return nullptr;
	}

	TArray<AActor*> arr;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARouteNode::StaticClass(), arr);

	if (arr.Num() == 0)
	{
		//Failed
		return nullptr;
	}

	arr.Sort([owner](const AActor& a, const AActor& b)
		{
			float toA = FMath::Abs(owner->GetActorLocation().X - a.GetActorLocation().X)
				+ FMath::Abs(owner->GetActorLocation().Y - a.GetActorLocation().Y);
			float toB = FMath::Abs(owner->GetActorLocation().X - b.GetActorLocation().X)
				+ FMath::Abs(owner->GetActorLocation().Y - b.GetActorLocation().Y);
			return toA < toB;
		});

	ARouteNode* result = Cast<ARouteNode>(arr[0]);

	return result;
}

void URouteFindComponent::FindRoute()
{
	ARouteNode* first = FindNearestRouteNode();

	//TODO :Set
	ARouteNode* destination = nullptr;

	if (!IsValid(first))
	{
		return;
	}

	//탐색을 위한 큐
	TArray<URouteInfo*> q;

	//이미 탐색한 노드 체크용도
	TArray<ARouteNode*> visited;

	//노드 정보 모음
	TArray<URouteInfo*> have;

	//시작 정보
	URouteInfo* firstInfo = NewObject<URouteInfo>();
	firstInfo->RouteNode = first;
	firstInfo->RouteParentInfo = nullptr;
	firstInfo->F = 0;
	firstInfo->G = 0;

	q.Add(firstInfo);
	visited.Add(first);

	TArray<AActor*> nodeArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARouteNode::StaticClass(), nodeArr);

	URouteInfo* resultDest = nullptr;

	while (q.Num() > 0)
	{
		if (q.Num() > 1)
		{
			//새롭게 받은 큐의 정보들을 F가 가장 작은 기준으로 정렬함.
			q.Sort([](const URouteInfo& a, const URouteInfo& b)
				{
					return (a.F) < (b.F);
				});
		}

		URouteInfo* nodeInfo = q.Pop();

		const float AllowedDistance = 50000.0f;

		for (AActor* i : nodeArr)
		{
			//nodeinfo의 노드와 같은 노드라면 스킵.
			if (nodeInfo->RouteNode == i)
			{
				continue;
			}

			//이미 방문했다면 스킵.
			if (nodeArr.Find(i) != -1)
			{
				continue;
			}

			//거리 계산해서 적당한 거리만 추출.
			float distance = FMath::Abs(nodeInfo->RouteNode->GetActorLocation().X - i->GetActorLocation().X) + FMath::Abs(nodeInfo->RouteNode->GetActorLocation().Y - i->GetActorLocation().Y);
			if (distance <= AllowedDistance)
			{
				ARouteNode* current = Cast<ARouteNode>(i);
				// 실패시 스킵.
				if (IsValid(current))
				{
					continue;
				}

				//목적지라면 목적지 정보를 추출하고 로직을 끝냄. q.Empty()가 동작하면 자동으로 while도 끝남.
				if (current == destination)
				{
					resultDest = NewObject<URouteInfo>();
					resultDest->G = distance;
					resultDest->F = nodeInfo->F + resultDest->G;
					resultDest->RouteNode = destination;
					resultDest->RouteParentInfo = nodeInfo;
					q.Empty();
					break;
				}

				//성공했다면 큐에 넣는다.
				URouteInfo* nextNodeInfo = NewObject<URouteInfo>();
				nextNodeInfo->G = distance;
				nextNodeInfo->F = nodeInfo->F + nextNodeInfo->G;
				nextNodeInfo->RouteNode = current;
				nextNodeInfo->RouteParentInfo = nodeInfo;
				q.Add(nextNodeInfo);

				//현재 노드를 방문 체크함.
				visited.Add(current);
				
				//마지막에 node 검색을 위해서 node 정보를 다 저장함.
				have.Add(nextNodeInfo);
			}

		}

	}

	//루트 결과물
	TArray<ARouteNode*> routeResult;
	
	//Parent가 존재하지 않을때까지 선형탐색함
	URouteInfo* temp = resultDest;
	while (IsValid(temp))
	{
		routeResult.Add(temp->RouteNode);
		temp = temp->RouteParentInfo;
	}

	//Warning : routeResult 역순이 결과물일거임.

}

