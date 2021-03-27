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
#include "Base.h" //Interactive
#include "GameFramework/CharacterMovementComponent.h"
#include "BasicWeapon.h"
#include "Blueprint/UserWidget.h" // CreateWidget
#include "BasicPlayerController.h"
#include "../Inventory/EquipmentComponent.h"
#include "SpeechWidgetComponent.h"
#include "DamageTextActor.h"
#include "Components/SceneComponent.h"
#include "../Puzzle/PhysicsHoldBase.h"

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
	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));

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

}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	//init Camera Setting.
	SettingWithCameraType();

}

float ABasicCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Stat) // Only Stat is Exist...
	{

		if (Stat->HP <= 0.0f)
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

		if (DamageEvent.DamageTypeClass != NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *DamageEvent.DamageTypeClass->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NULL?"));
		}

		Stat->DealDamage(damageResult);
		UE_LOG(LogTemp, Warning, TEXT("Current HP : %f"), Stat->HP);

		if (DamageTextActorClass)
		{
			ADamageTextActor* damageTextActor = GetWorld()->SpawnActorDeferred<ADamageTextActor>(DamageTextActorClass, GetActorTransform());
			if (damageTextActor)
			{
				damageTextActor->AppliedDamage = damageResult;
				damageTextActor->FinishSpawning(GetActorTransform());
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

	InteractCheck();
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
		//PlayerController Default Yaw Scale Input is 2.5f. so to rotate -90 degree, -36*2.5 = 90.
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
	if (bHoldSomething)
	{
		return;
	}

	/*First, LineTrace Detection. First Priority is Actor's look Direction.*/
	/*second Priority is Overlapped Actor detection & most Closest Actor.*/

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;

	//objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	//objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> ignores;
	ignores.Add(this);
	ignores.Add(CurrentWeapon);

	FHitResult hit;

	FVector traceStart = GetActorLocation() + FVector(0.0f, 0.0f, -50.0f); // A little Downward of Trace Start Location.
	FVector traceEnd = traceStart + GetActorForwardVector() * 100.0f;

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

	bool bCheck = false;
	AActor* Interactee = nullptr;

	if (result)
	{
		AActor* actor = hit.GetActor();
		if (actor && actor->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
		{
			//if (GEngine)
			//{
			//FString temp = FString("Current Interact Check : ") + actor->GetName();
			//GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Silver, temp);
			//}

			bCheck = true;
			Interactee = actor;
		}
	}
	else
	{
		/*Line Trace Failed... Use Overlap Detection*/
		TArray<AActor*> overlapped;

		GetOverlappingActors(overlapped);

		//Sort by Distance. descending order. lambda function.
		overlapped.Sort(
			[this](const AActor& a, const AActor& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetActorLocation())
					< FVector::Distance(GetActorLocation(), b.GetActorLocation());
			}
		);

		///*Result*/
		//UE_LOG(LogTemp, Warning, TEXT("----After sort---"));
		for (AActor* i : overlapped)
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor Name : %s"), *i->GetName());
		}

		if (overlapped.Num() > 0)
		{
			AActor* firstOverlap = overlapped[0];

			if (IsValid(firstOverlap) && firstOverlap->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
			{
				//if (GEngine)
				//{
				//	//FString temp = FString("Overlap Current Interact Check : ") + firstOverlap->GetName();
				//	//GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Green, temp);
				//}

				bCheck = true;
				Interactee = firstOverlap;
			}
		}
	}


	ABasicPlayerController* playerController = GetController<ABasicPlayerController>();
	if (playerController)
	{
		if (bCheck)
		{
			if (IsValid(Interactee))
			{
				playerController->NotifyInteract(Interactee);
			}
		}
		else
		{
			playerController->UnnotifyInteract();
		}

	}

}

void ABasicCharacter::InteractTrigger()
{

	if (bHoldSomething)
	{
		UnHold();
		return;
	}


	/*First, LineTrace Detection. First Priority is Actor's look Direction.*/
	/*second Priority is Overlapped Actor detection & most Closest Actor.*/

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;

	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	//objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	objects.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<AActor*> ignores;
	ignores.Add(this);
	ignores.Add(CurrentWeapon);

	FHitResult hit;

	FVector traceStart = GetActorLocation() + FVector(0.0f, 0.0f, -50.0f); // A little Downward of Trace Start Location.
	FVector traceEnd = traceStart + GetActorForwardVector() * 100.0f;

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

	if (result)
	{
		AActor* actor = hit.GetActor();
		if (actor->GetClass()->ImplementsInterface(UInteractive::StaticClass())) //Detecting Interface
		{
			IInteractive::Execute_Interact(actor, this);
		}
	}
	else
	{
		/*Line Trace Failed... Use Overlap Detection*/
		TArray<AActor*> overlapped;

		GetOverlappingActors(overlapped);

		//Sort by Distance. descending order. lambda function.
		overlapped.Sort(
			[this](const AActor& a, const AActor& b)
			->bool {
				return FVector::Distance(GetActorLocation(), a.GetActorLocation())
					< FVector::Distance(GetActorLocation(), b.GetActorLocation());
			}
		);

		///*Result*/
		//UE_LOG(LogTemp, Warning, TEXT("----After sort---"));
		//for (AActor* i : overlapped)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Actor Name : %s"), *i->GetName());
		//}

		if (overlapped.Num() > 0)
		{
			AActor* firstOverlap = overlapped[0];

			if (IsValid(firstOverlap))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"),*firstOverlap->GetName());
				if (firstOverlap->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
				{
					
					IInteractive::Execute_Interact(firstOverlap,this);
					//UE_LOG(LogTemp, Warning, TEXT("Interact OK.."));
				}
			}
		}

	}

}

void ABasicCharacter::ToggleInventory()
{
	ABasicPlayerController* playerController = GetController<ABasicPlayerController>();

	if (playerController)
	{
		playerController->ToggleInventory();
	}
}

void ABasicCharacter::Hold(APhysicsHoldBase* ToHold)
{
	if (IsValid(ToHold))
	{
		bHoldSomething = true;
		CurrentHold = ToHold;
		ToHold->SetHoldStatus(true);
		ToHold->AttachToComponent(HoldPosition,FAttachmentTransformRules::KeepWorldTransform);
		ToHold->SetActorLocation(HoldPosition->GetComponentLocation());
	}
}

void ABasicCharacter::UnHold()
{

	if (CurrentHold)
	{
		bHoldSomething = false;
		CurrentHold->SetHoldStatus(false);
		CurrentHold->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentHold->ThrowToDirection(GetActorForwardVector());
	}
}

void ABasicCharacter::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("C++ Interact()"));
}

