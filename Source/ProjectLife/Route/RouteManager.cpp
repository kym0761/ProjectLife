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
//	//TODO : ��û�� ���� �ʿ���.
//	ARouteNode* first = FindNearestRouteNode(nullptr);
//
//	//first�� ������ ����
//	if (!IsValid(first))
//	{
//		return;
//	}
//
//	//Ž���� ���� ť
//	TQueue<ARouteNode*> q;
//	//�̹� Ž���� ��� üũ�뵵
//	TArray<ARouteNode*> visited;
//
//	//����� ���;��� ������ ���?
//	ARouteNode* resultDest;
//
//	//���� ��� ����
//	q.Enqueue(first);
//
//	while (!q.IsEmpty())
//	{
//		ARouteNode* node = *q.Peek();
//		q.Pop();
//
//		//TODO : ������ ������ �ʿ�. �������� ã���� while�� ������������.
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
//			//�湮�� �� �ִ� ���� ��ŵ��. �ʿ����.
//			if (visited.Find(arr[i]) == INDEX_NONE)
//			{
//				continue;
//			}
//
//			//�湮�Կ� �ְ�, q�� �ִ´�.
//			visited.Add(arr[i]);
//			q.Enqueue(arr[i]);
//			//RouteParent�� ������. 
//			arr[i]->RouteParent = node;
//		}
//
//	}
//
//	//�������� ��ã���� ����
//	if (!IsValid(resultDest))
//	{
//		return;
//	}
//
//
//	//����� ���� ������������ ��Ʈ
//	TArray<ARouteNode*> resultRoute;
//	
//	ARouteNode* temp = resultDest;
//	
//	//RouteParent�� �˻��ؼ� null�� ���ö����� ã�´�. first�� Route Parent�� ���� ���̴�.
//	while (IsValid(temp))
//	{
//		resultRoute.Add(temp);
//		temp = temp->RouteParent;
//	}
//	
//	//TODO : �������� �ؾ� ��Ʈ��.
//
//
//
//}
//
