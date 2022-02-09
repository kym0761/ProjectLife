// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	for (int32 i = 0; i < 30; i++)
	{
		Items.Add(FItemDataSlot());
	}

	//temp
	Money = 10000;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Disabled
}

bool UInventoryComponent::CheckInventoryHasSpace()
{
	bool bHasSpace = false;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Quantity == 0)
		{
			bHasSpace = true;
			break;
		}
	}

	return bHasSpace;
}

bool UInventoryComponent::SpendMoney(int32 Spend)
{
	if (Money < Spend)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Can't Spend Money, Demand is Over the In-Hand"));
		}

		return false;
	}
	else
	{
		Money = FMath::Clamp(Money - Spend, 0, TNumericLimits<int32>::Max());
		return true;
	}
}

void UInventoryComponent::GainMoney(int32 Gain)
{
	Money = FMath::Clamp(Money + Gain, 0, TNumericLimits<int32>::Max());

	if (Money == TNumericLimits<int32>::Max())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Warning! Your Money is Full."));
		}
	}
}

bool UInventoryComponent::CheckEnoughMoney(int32 ToCompare)
{
	if (Money >= ToCompare)
	{
		return true;
	}

	return false;
}

void UInventoryComponent::TryMakeInventorySpace(int32 Num)
{
	//�� ������ ����
	FItemDataSlot slot;
	for (int32 i = 0; i < Num; i++)
	{
		Items.Add(slot);
	}
}

bool UInventoryComponent::SwapItemBetweenInventory(UInventoryComponent* From, int32 FromSlot, UInventoryComponent* To, int32 ToSlot)
{
	if (!(IsValid(From) && IsValid(To)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Valid Inventory"));
		return false;
	}

	if (From->Items.IsValidIndex(FromSlot) && To->Items.IsValidIndex(ToSlot))
	{
		FItemDataSlot i1 = From->Items[FromSlot];
		FItemDataSlot i2 = To->Items[ToSlot];

		if (!From->Items[FromSlot].IsSameItem(To->Items[ToSlot])) //�ٸ� �������� ����ִ� �����̶��, Swap��.
		{
			From->Items[FromSlot] = i2;
			To->Items[ToSlot] = i1;

			return true;
		}
		else  //���� �������� �����Ѵٸ� join
		{
			//������ ���� �� ����. �ӽ÷� ����.
			UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (!IsValid(gameInstance))
			{
				UE_LOG(LogTemp, Warning, TEXT("Access GameInstance Failed"));
				return false;
			}

			FItemData itemData = gameInstance->GetItemDataFromTable(i1.ItemName); // Get Item Data

			if (itemData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot ������ FromSlot ������ ���� �� ���Կ� �� ������ ����ϸ�.. "ToSlot"�� �������� ���� ��. "FromSlot"�� �� ������ ��.
			{
				i1.Quantity += i2.Quantity;
				i2 = FItemDataSlot();

				From->Items[FromSlot] = i2;
				To->Items[ToSlot] = i1;

				//UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
				return true;
			}
			else //���� ���ļ� �ִ� ������ �ʰ��ϸ�.. "ToSlot"���� Max Quantity ��ŭ �� , "FromSlot"���� �������� ��.
			{
				int32 temp = i1.Quantity + i2.Quantity;
				i1.Quantity = itemData.MaxQuantity;

				temp -= i1.Quantity;
				i2.Quantity = temp;

				From->Items[FromSlot] = i2;
				To->Items[ToSlot] = i1;

				//UE_LOG(LogTemp, Warning, TEXT("join2 Success"));
				return true;
			}
		}
	}

	return false;
}

FItemDataSlot UInventoryComponent::GetInventoryItem(int32 SlotNumber)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		//������ � ��?
		return Items[SlotNumber];
	}

	//���н� ��.
	return FItemDataSlot();
}

bool UInventoryComponent::SetInventoryItem(int32 SlotNumber, FItemDataSlot InData)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		Items[SlotNumber] = InData;
		return true;
	}

	return false;
}

int32 UInventoryComponent::AddItemToInventory(FItemDataSlot InData)
{
	// -1 ���� ����, 0 --> ���������� �� ��, 1 �̻�--> ����.

	if (InData.IsEmpty())
	{
		// �� ������ ���� ����.
		return -1;
	}

	UProjectLIfeGameInstance* gameinstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (!IsValid(gameinstance))
	{
		return -1;
	}

	FItemData itemData = gameinstance->GetItemDataFromTable(InData.ItemName);
	if (itemData.IsEmpty())
	{
		//�߸��� ����. ���� ����.
		return -1;
	}


	//!! : ���� �� ���̶� ��� �ƴٸ�, �κ��丮�� �ݿ��� �ǹǷ� FItemDataSlot�� �� ���� ���� �ȵ�.
	FItemDataSlot leftover = InData;
	for (int i = 0; i < Items.Num(); i++)
	{
		//�κ��丮���� �ְ� ���� �����۰� ���� �������� ������ ã��, ���� �� �� ������ �ƴ϶�� ���빰�� ä���.
		if (Items[i].ItemName == leftover.ItemName && Items[i].Quantity < itemData.MaxQuantity)
		{
			int32 extra = itemData.MaxQuantity - Items[i].Quantity;
			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

			Items[i].Quantity += tempOffset;

			leftover.Quantity -= tempOffset;

			if (leftover.Quantity == 0)
			{
				//������ ������ ����.
				return 0;
			}
			else if (leftover.Quantity < 0)
			{
				//������ ������ �ֱ���. �ٸ�, �κ��丮�� �ݿ��� �����Ƿ� �ϴ� 0���� ���
				return 0;
			}
		}
	}
	//������� �Դٸ�, leftover�� ���� �����ְų�, Ȥ�� ���� ������ ã�� ����.
	//�� ���� ������ ������ �ִ´�.
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{
			SetInventoryItem(i, leftover);
			return 0;
		}
	}
	//Warning 1 : leftover�� �������� �ణ ����µ�, �ٴڿ� ������ ������ ó���� ����� ���� ����.
	//Warning 2 : ������ ������ �ߴµ�, ������ �ʰ��Ǽ� ���� or �κ��丮 ������ ��� ������ �ƿ� ���� ����.
	return leftover.Quantity;


}

bool UInventoryComponent::CheckPlayerInventoryHasSpace()
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		FItemDataSlot item = Items[i];
		if (item.IsEmpty())
		{
			return true;
		}
	}

	return false;
}

