// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "GameFramework/SpringArmComponent.h" //SpringArm
#include "Camera/CameraComponent.h" //Camera
#include "Kismet/KismetMathLibrary.h" //UKismetMathLibrary
#include "Kismet/KismetSystemLibrary.h" //UKismetSystemLibrary
#include "Kismet/GameplayStatics.h" //UGamePlayStatics
#include "Components/SkeletalMeshComponent.h"
#include  "StatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BasicWeapon.h"
#include "Blueprint/UserWidget.h" // CreateWidget
#include "BasicPlayerController.h"
#include "Equipment/EquipmentComponent.h"
#include "SpeechWidgetComponent.h"
#include "DamageTextActor.h"
#include "Components/SceneComponent.h"
#include "Grid/GridDetectComponent.h"
#include "Ability/AbilityComponent.h"
#include "InteractDetectComponent.h"

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

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
	GridDetectComponent = CreateDefaultSubobject<UGridDetectComponent>(TEXT("GridDetectComponent"));
	
	InteractDetectComponent = CreateDefaultSubobject<UInteractDetectComponent>(TEXT("InteractDetectComponent"));
	InteractDetectComponent->SetupAttachment(RootComponent);
	InteractDetectComponent->InitSphereRadius(96.0f);
	InteractDetectComponent->SetRelativeLocation(FVector(80.0f, 0.0f, 0.0f));

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
	//NotifyInteract UI를 보여주어 현재 Interact가 가능한지 보여주기 위한 기능

	//Disable the Check When Hold Something.
	if (bHoldSomething)
	{
		return;
	}

	//UObject* interactee = FindInteractee();
	AActor* interactee = InteractDetectComponent->GetInteractiveActor();

	//Interact Check
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

}

void ABasicCharacter::InteractTrigger()
{
	//참고 : PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABasicCharacter::InteractTrigger);
	//Interact 실행.

	//Disable the Check When Hold Something.
	if (bHoldSomething)
	{
		//UnHold();
		return;
	}

	//UObject* interactee = FindInteractee();
	AActor* interactee = InteractDetectComponent->GetInteractiveActor();

	//check valid and Interact Execute.
	if (IsValid(interactee) && interactee->GetClass()->ImplementsInterface(UInteractive::StaticClass()))
	{
		IInteractive::Execute_Interact(interactee, this);
	}
}

void ABasicCharacter::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("C++ Interact(). Override Needed?"));
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
