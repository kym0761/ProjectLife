
# ProjectLife

농장 시뮬레이션과 던전 탐험 및 퍼즐 게임을 합쳐 다양한 요소를 즐길 수 있는 게임을 개발하고자 시작한 프로젝트.

# Inventory System

인벤토리는 FItemSlotData라는 정보를 배열로 저장한다.

현재 FItemSlotData는 (아이템 이름, 개수) 정보를 가지고 있으며, 실제 아이템 정보는 FItemData의 데이터 테이블에서 실제 아이템 정보를 불러오는 기능을 가지고 있다.

<img src="ExplainImages/inventory01.png" width="50%">

#InventoryComponent

<img src="ExplainImages/inventory02.png" width="50%">

UInventoryComponent는 실질적인 인벤토리 기능을 담당한다.

인벤토리를 보유하는 Actor는 현재 ABasicPlayerController, AStorageBox, ACookActor이다.

1. 플레이어는 캐릭터가 인벤토리를 보유하는 것이 아니라 PlayerController가 보유하여 컨트롤하는 캐릭터가 바뀌어도 인벤토리는 같은 것을 사용할 수 있도록 했다.
2. AStorageBox는 맵에 존재하는 보관함으로 인벤토리를 보유한다.
3. ACookActor는 제조 기능(요리)을 위해 인벤토리에서 아이템을 보유하고, ACookActor의 인벤토리에 있는 재료를 기반으로 제작해 준다.

추후 다른 Actor들도 인벤토리를 보유할 수도 있으므로, 컴포넌트를 추가만으로 인벤토리의 다양한 기능을 쉽게 적용할 수 있다.

<img src="ExplainImages/inventory03.png" width="50%">

UInventoryComponent는 OnInventoryDataChanged를 통해 인벤토리의 데이터의 변경이 있을 시에 Broadcast()하여 인벤토리의 내용을 출력하는 UI들의 내용을 변경시켜 준다.


