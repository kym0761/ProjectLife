// Fill out your copyright notice in the Description page of Project Settings.


#include "RouteManager.h"
#include "RouteNode.h"
// Sets default values
ARouteManager::ARouteManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARouteManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARouteManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//ARouteNode* ARouteManager::FindNearestRouteNode(AActor* Requestor)
//{
//	//TODO FindNearest
//
//	return nullptr;
//}
//
//void ARouteManager::FindRoute()
//{
//
//	//TODO : 요청자 설정 필요함.
//	ARouteNode* first = FindNearestRouteNode(nullptr);
//
//	//first가 없으면 실패
//	if (!IsValid(first))
//	{
//		return;
//	}
//
//	//탐색을 위한 큐
//	TQueue<ARouteNode*> q;
//	//이미 탐색한 노드 체크용도
//	TArray<ARouteNode*> visited;
//
//	//결과로 나와야할 목적지 노드?
//	ARouteNode* resultDest;
//
//	//최초 노드 설정
//	q.Enqueue(first);
//
//	while (!q.IsEmpty())
//	{
//		ARouteNode* node = *q.Peek();
//		q.Pop();
//
//		//TODO : 목적지 설정이 필요. 목적지를 찾으면 while을 빠져나가야함.
//		//if (node = dest)
//		//{
//		//	q.Empty();
//		// resultDest = node;
//		//	break;
//		//}
//
//		TArray<ARouteNode*> arr = node->NearNodes;
//
//		for (int32 i = 0; i < arr.Num(); i++)
//		{
//			//방문한 적 있는 노드는 스킵함. 필요없음.
//			if (visited.Find(arr[i]) == INDEX_NONE)
//			{
//				continue;
//			}
//
//			//방문함에 넣고, q에 넣는다.
//			visited.Add(arr[i]);
//			q.Enqueue(arr[i]);
//			//RouteParent를 지정함. 
//			arr[i]->RouteParent = node;
//		}
//
//	}
//
//	//목적지를 못찾으면 실패
//	if (!IsValid(resultDest))
//	{
//		return;
//	}
//
//
//	//결과로 나올 목적지까지의 루트
//	TArray<ARouteNode*> resultRoute;
//	
//	ARouteNode* temp = resultDest;
//	
//	//RouteParent를 검색해서 null이 나올때까지 찾는다. first는 Route Parent가 없을 것이다.
//	while (IsValid(temp))
//	{
//		resultRoute.Add(temp);
//		temp = temp->RouteParent;
//	}
//	
//	//TODO : 역순으로 해야 루트임.
//
//
//
//}
//
