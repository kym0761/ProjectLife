// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "GameFramework/SpringArmComponent.h" //SpringArm
#include "Camera/CameraComponent.h" //Camera
#include "Kismet/KismetMathLibrary.h" //UKismetMathLibrary
#include "Kismet/KismetSystemLibrary.h" //UKismetSystemLibrary
#include "Kismet/GameplayStatics.h" //UGamePlayStatics
#include "Components/SkeletalMeshComponent.h"
#include "../Inventory/InventoryComponent.h"
#include  "StatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BasicWeapon.h"
#include "Blueprint/UserWidget.h" // CreateWidget
#include "BasicPlayerController.h"
#include "../Equipment/EquipmentComponent.h"
#include "SpeechWidgetComponent.h"
#include "DamageTextActor.h"
#include "Components/SceneComponent.h"

#include "../Grid/GridComponent.h"
#include "../Grid/GridManager.h"

#include "../Ability/AbilityComponent.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f);

	SpringArm->ProbeChannel = ECollisionChannel::ECC_GameTraceChannel1;
	SpringArm->bEnableCameraRotationLag = true;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(0.0f,0.0f,300.0f));

	Camera->PostProcessSettings.bOverride_MotionBlurAmount = true;
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	//Set Default Mesh Transform
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	CameraType = ECameraType::TopView;

	SpeechBubbleWidget = CreateDefaultSubobject<USpeechWidgetComponent>(TEXT("SpeechBubbleWidget"));
	SpeechBubbleWidget->SetupAttachment(RootComponent);
	SpeechBubbleWidget->SetRelativeLocation(FVector(0.0f,0.0f,110.0f));
	SpeechBubbleWidget->SetPivot(FVector2D(0.125f,0.5f));

	HoldPosition = CreateDefaultSubobject<USceneComponent>(TEXT("HoldPosition"));
	HoldPosition->SetupAttachment(RootComponent);
	bHoldSomething = false;

	CurrentHold = nullptr;


}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	//init Camera Setting.
	SettingWithCameraType();

	//InteractCheck with Interval.
	GetWorldTimerManager().SetTimer(InteractCheckTimer, this, &ABasicCharacter::InteractCheck, InteractCheckInterval, true);

}

float ABasicCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//TODO : ReMake Take Damage.

	if (IsValid(StatComponent)) // Only Stat is Exist...
	{

		if (StatComponent->HP <= 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("HP is 0"));

			if (DamageTextActorClass)
			{
				ADamageTextActor* damageTextActor = GetWorld()->SpawnActorDeferred<ADamageTextActor>(DamageTextActorClass, GetActorTransform());
				if (damageTextActor)
				{
					damageTextActor->AppliedDamage = 0.0f;
					damageTextActor->FinishSpawning(GetActorTransform());
				}
			}

			return 0.0f;
		}

		float damageResult = DamageAmount;

		//if (DamageEvent.DamageTypeClass != NULL)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("%s"), *DamageEvent.DamageTypeClass->GetName());
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("NULL?"));
		//}

		StatComponent->DealDamage(damageResult);
		//UE_LOG(LogTemp, Warning, TEXT("Current HP : %f"), Stat->HP);

		if (DamageTextActorClass)
		{
			ADamageTextActor* damageTextActor = GetWorld()->SpawnActorDeferred<ADamageTextActor>(DamageTextActorClass, GetActorTransform());
			if (damageTextActor)
			{
				damageTextActor->AppliedDamage = damageResult;

				FTransform transform = GetActorTransform();
				transform.SetLocation(transform.GetLocation() + FVector(FMath::FRandRange(-50.0f, 50.0f), FMath::FRandRange(-50.0f, 50.0f), 0.0f));
				damageTextActor->FinishSpawning(transform);
			}
		}


		return damageResult;
	}
	else
	{
		return -1.0f;
	}
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &ABasicCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABasicCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABasicCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasicCharacter::LookUp);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasicCharacter::InteractTrigger);
	PlayerInputComponent->BindAction("RotateCamera", IE_Pressed, this, &ABasicCharacter::RotateTopView);
	PlayerInputComponent->BindAction("RotateCamera_Reverse", IE_Pressed, this, &ABasicCharacter::RotateTopView_Reverse);
	PlayerInputComponent->BindAction("ChangeCameraType", IE_Pressed, this, &ABasicCharacter::ChangeCameraType);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasicCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABasicCharacter::StopJumping);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ABasicCharacter::ToggleInventory);

}

void ABasicCharacter::MoveForward(float Value)
{
	FVector cameraLocation;
	FRotator cameraRotation;
	GetController()->GetPlayerViewPoint(cameraLocation, cameraRotation);

	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);

	FVector temp = UKismetMathLibrary::GetForwardVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABasicCharacter::MoveRight(float Value)
{
	FVector cameraLocation;
	FRotator cameraRotation;
	GetController()->GetPlayerViewPoint(cameraLocation, cameraRotation);

	FRotator controlRot = FRotator(0.0f, cameraRotation.Yaw, 0.0f);

	FVector temp = UKismetMathLibrary::GetRightVector(controlRot);

	AddMovementInput(temp, Value);
}

void ABasicCharacter::Turn(float Value)
{
	if (CameraType == ECameraType::ThirdPersonView)
	{
		AddControllerYawInput(Value);
	}

}

void ABasicCharacter::LookUp(float Value)
{
	if (CameraType == ECameraType::ThirdPersonView)
	{
		AddControllerPitchInput(-Value);
	}
	
}

void ABasicCharacter::RotateTopView()
{
	if (CameraType == ECameraType::TopView)
	{
		//PlayerController Default Yaw Scale Input is 2.5f. so to rotate 90 degree, 36*2.5 = 90.
		AddControllerYawInput(36.0f);
	}
}

void ABasicCharacter::RotateTopView_Reverse()
{
	if (CameraType == ECameraType::TopView)
	{
		//PlayerController Default Yaw Scale Input is 2.5f. so to rotate -90 degree, -36*2.5 = -90.
		AddControllerYawInput(-36.0f);
	}
}

void ABasicCharacter::ChangeCameraType()
{
	//Toggle CameraMode.
	switch (CameraType)
	{
	case ECameraType::TopView:
		CameraType = ECameraType::ThirdPersonView;
		break;
	case ECameraType::ThirdPersonView:
		CameraType = ECameraType::TopView;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown CameraType"));
		break;
	}

	SettingWithCameraType();
}

void ABasicCharacter::SettingWithCameraType()
{
	if (IsPlayerControlled())
	{
		//Setting With CameraMode
		switch (CameraType)
		{
		case ECameraType::TopView:
			SpringArm->bEnableCameraRotationLag = true;
			GetController()->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
			break;
		case ECameraType::ThirdPersonView:
			SpringArm->bEnableCameraRotationLag = false;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown CameraType"));
			break;
		}
	}
}

void ABasicCharacter::InteractCheck()
{
	//Disable the Check When Hold Something.
	if (bHoldSomething)
	{
		return;
	}

	UObject* interactee = FindInteractee();

	ABasicPlayerController* playerController = GetController<ABasicPlayerController>();
	if (playerController)
	{

		if (IsValid(interactee) && interactee->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			playerController->NotifyInteract(interactee);
		}
		else
		{
			playerController->UnnotifyInteract();
		}

	}

	AGridManager* gridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass()));
	UGridComponent* grid = Cast<UGridComponent>(interactee);
	if (IsValid(gridManager) && IsValid(grid))
	{
		gridManager->DrawAvailableMesh(grid);
	}
	else if (IsValid(gridManager) && !IsValid(grid))
	{
		gridManager->RemoveAvailableMesh();
	}

}

void ABasicCharacter::InteractTrigger()
{

	//if Hold Something, Unhold And End Interaction Trigger.
	if (bHoldSomething)
	{
		UnHold();
		return;
	}

	UObject* interactee = FindInteractee();

	//check valid and Interact Execute.
	if (IsValid(interactee) && interactee->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
	{
		IInteractive::Execute_Interact(interactee, this);
	}
}

UObject* ABasicCharacter::FindInteractee()
{
	/*First, LineTrace Detection. First Priority is Actor's look Direction.*/
	/*second Priority is Overlapped Actor detection & most Closest Actor.*/

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;

	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	objects.Add(EObjectTypeQuery::ObjectTypeQuery7); // interact object type.

	TArray<AActor*> ignores;
	ignores.Add(this);
	ignores.Add(CurrentWeapon);
	ignores.Add(CurrentHold);

	FVector traceStart = GetActorLocation() + FVector(0.0f, 0.0f, -50.0f); // A little Downward of Trace Start Location.
	FVector traceEnd = traceStart + GetActorForwardVector() * 100.0f;

	FHitResult hit;

	bool result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		traceStart,
		traceEnd,
		objects,
		true,
		ignores,
		EDrawDebugTrace::None, 
		//EDrawDebugTrace::ForDuration,
		hit,
		true,
		FLinearColor::Red,
		FLinearColor::Blue,
		5.0f
	);

	UObject* interactee = nullptr;

	if (result)
	{
		AActor* actor = hit.GetActor();
		if (IsValid(actor) && actor->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			//bCheck = true;
			interactee = actor;
		}

		UPrimitiveComponent* comp = hit.GetComponent();
		if (IsValid(comp) && comp->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Interactive Component Call Ok."));
			interactee = comp;
		}

	}
	
	//if interactee still not Valid.. Line Trace Failed... Use Overlap Detection.
	if(!IsValid(interactee))
	{
		TArray<AActor*> overlapped;

		GetOverlappingActors(overlapped);

		//Sort by Distance. descending order.
		overlapped.Sort(
			[this](const AActor& a, const AActor& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetActorLocation())
					< FVector::Distance(GetActorLocation(), b.GetActorLocation());
			}
		);

		for (AActor* i : overlapped)
		{
			if (IsValid(i) && i->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
			{
				interactee = i;
				break;
			}
		}
	}

	/*Actor Interactive Find would be Failed.  maybe, Is Your Intention To Find Component?*/
	if (!IsValid(interactee))
	{
		TArray<UPrimitiveComponent*> overlappedComponents;
		GetOverlappingComponents(overlappedComponents);

		//Sort by Distance. descending order.
		overlappedComponents.Sort(
			[this](const UPrimitiveComponent& a, const UPrimitiveComponent& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetComponentLocation())
					< FVector::Distance(GetActorLocation(), b.GetComponentLocation());
			}
		);

		for (UPrimitiveComponent* i : overlappedComponents)
		{
			if (IsValid(i) && i->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
			{
				interactee = i;
				break;
			}
		}
	}

	if (IsValid(interactee))
	{
		return interactee;
	}
	else
	{
		return nullptr;
	}
}

void ABasicCharacter::ToggleInventory()
{
	ABasicPlayerController* playerController = GetController<ABasicPlayerController>();

	if (IsValid(playerController))
	{
		playerController->ToggleInventory();
	}
}

void ABasicCharacter::Hold(AActor* ToHold)
{
	if (IsValid(ToHold))
	{
		//set
		bHoldSomething = true;
		CurrentHold = ToHold;
		
		//if has Primitive, Physics Off.
		UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(CurrentHold->GetRootComponent());
		if (IsValid(rootComp))
		{
			rootComp->SetSimulatePhysics(false);
		}

		//Attach.
		ToHold->AttachToComponent(HoldPosition,FAttachmentTransformRules::KeepWorldTransform);
		ToHold->SetActorRelativeRotation(FRotator::ZeroRotator);
		ToHold->SetActorLocation(HoldPosition->GetComponentLocation());
	}
}

void ABasicCharacter::UnHold()
{

	if (IsValid(CurrentHold))
	{
		//if Root is Primitive, then Physics On.
		UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(CurrentHold->GetRootComponent());
		if (IsValid(rootComp))
		{
			rootComp->SetSimulatePhysics(true);
		}

		//detach from character.
		CurrentHold->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentHold->SetActorRotation(FRotator::ZeroRotator);
		
		//Throw.
		if (IsValid(rootComp) && rootComp->IsSimulatingPhysics())
		{
			FVector power = GetActorForwardVector() * 500.0f * rootComp->GetMass();
			rootComp->AddImpulse(power);
		}

		//Reset
		bHoldSomething = false;
		CurrentHold = nullptr;
	}
}

void ABasicCharacter::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("C++ Interact(). Override Needed?"));
}

