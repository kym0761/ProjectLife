# 목차

[1. ProjectLife](#projectlife)
[2. Inventory System](#inventory-system)
[3. InventoryComponent](#inventorycomponent)
[4. InventoryUI](#inventory-ui)
[5. Drag Drop](#drag-drop)
[6. Shop](#shop)


# ProjectLife

농장 시뮬레이션과 던전 탐험 및 퍼즐 게임을 합쳐 다양한 요소를 즐길 수 있는 게임을 개발하고자 시작한 프로젝트.

# Inventory System

인벤토리는 FItemSlotData라는 정보를 배열로 저장한다.

현재 FItemSlotData는 (아이템 이름, 개수) 정보를 가지고 있으며, 실제 아이템 정보는 FItemData의 데이터 테이블에서 실제 아이템 정보를 불러오는 기능을 가지고 있다.

<img src="ExplainImages/inventory01.png" width="50%">

# InventoryComponent

<img src="ExplainImages/inventory02.png" width="50%">

UInventoryComponent는 실질적인 인벤토리 기능을 담당한다.

인벤토리를 보유하는 Actor는 현재 ABasicPlayerController, AStorageBox, ACookActor이다.

1. 플레이어는 캐릭터가 인벤토리를 보유하는 것이 아니라 PlayerController가 보유하여 컨트롤하는 캐릭터가 바뀌어도 인벤토리는 같은 것을 사용할 수 있도록 했다.
2. AStorageBox는 맵에 존재하는 보관함으로 인벤토리를 보유한다.
3. ACookActor는 제조 기능(요리)을 위해 인벤토리에서 아이템을 보유하고, ACookActor의 인벤토리에 있는 재료를 기반으로 제작해 준다.

추후 다른 Actor들도 인벤토리를 보유할 수도 있으므로, 컴포넌트를 추가만으로 인벤토리의 다양한 기능을 쉽게 적용할 수 있다.

<img src="ExplainImages/inventory03.png" width="50%">

UInventoryComponent는 OnInventoryDataChanged를 통해 인벤토리의 데이터의 변경이 있을 시에 Broadcast()하여 인벤토리의 내용을 출력하는 UI들의 내용을 변경시켜 준다.

# Inventory UI

<img src="ExplainImages/inventory01.png" width="50%">

Inventory UI는 크게 UInventoryWidget 과 UItemSlot으로 구성되어 있다.
UInventoryWidget은 UItemSlot을 여러 개 보유한 컨테이너의 개념이며, UItemSlot은 UInventoryComponent 안에 있는 아이템 정보를 출력 및 사용을 위한 버튼형 슬롯이다.
플레이어 인벤토리와 보관함 등의 서로 다른 아이템 공간에 Drag Drop으로 아이템을 옮길 수 있다.

<img src="ExplainImages/inventoryUI01.png" width="50%">

다음 예시는 UInventoryWidget의 코드의 일부.
UpdateInventoryWidget()은 UInventoryWidget가 보유한 UItemSlot들을 TArray<UItemSlot*> 형태로 보유하고 있으며 이 슬롯들의 정보를 갱신시켜주는 역할을 한다.
InitInventoryWidget()에서 인벤토리 UI를 초기화하고, UInventoryComponent의 Delegate에 UpdateInventoryWidget()을 bind한다.
인벤토리의 데이터가 바뀔 때마다 Delegate를 Broadcast()하여 UpdateInventoryWidget()가 호출된다.

# Drag Drop

<img src="ExplainImages/inventoryUI02.png" width="50%">

위의 이미지처럼 Drag Drop을 구현하여 인벤토리 내부를 정리할 수 있다.

<img src="ExplainImages/dragdrop01.png" width="50%">

UItemSlot::NativeOnDragDetected()의 코드 일부.

유저가 인벤토리 슬롯을 드래그하면 슬롯의 데이터를 그대로 복사한다.

이 작업을 하면 유저가 슬롯에 마우스 커서를 올리고 클릭한 뒤에 마우스를 움직이면 아이템 슬롯이 드래그 되며 마우스를 따라다닌다.

<img src="ExplainImages/dragdrop02.png" width="50%">

UItemSlot::NativeOnDrop()의 코드 일부.

위에서 만들어진 Drag가 다른 UItemSlot의 위에 놓인다면 두 슬롯의 데이터를 서로 바꾸는 기능을 한다.

# Shop

<img src="ExplainImages/shop01.png" width="50%">

위의 이미지처럼 푸른 실린더 액터에 Interact()하면 위의 이미지처럼 상점 UI가 나타난다.

<img src="ExplainImages/shop02.png" width="50%">

원하는 아이템 개수만큼 조절한 뒤에 OK를 누르면 구매가 확정되어 아이템이 인벤토리에 추가된다.

<img src="ExplainImages/shop03.png" width="50%">

AShoppingActor는 Interact가 가능한 Actor로 IInteractive 인터페이스를 보유하고 있어서 플레이어의 키보드 E를 누르면 Interact()가 호출되어 Interact할 수 있다.

<img src="ExplainImages/shop04.png" width="50%">

AShoppingActor의 Interact()는 플레이어가 AShoppingActor 앞에서 E버튼을 눌렀을 때, UShoppingWidget을 생성한다.

<img src="ExplainImages/shop05.png" width="50%">

AShoppingActor는 BeginPlay()에서 ShoppingDataTable을 읽어 자신이 판매할 아이템 데이터를 불러올 수 있다.
ShoppingDataTable는 미리 설정된 FTableRowBase를 상속한 구조체를 통해 데이터 테이블 블루프린트로 관리되어 있다.