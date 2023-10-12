// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bInteractOK = true;
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimal::Interact_Implementation(APawn* InteractCauser)
{
	if (bInteractOK)
	{
		bInteractOK = false;
	}
	else
	{
		return;
	}

	PlayInteractSound();
}

void AAnimal::WhenSoundFinished()
{
	bInteractOK = true;
}

void AAnimal::PlayInteractSound()
{
	if (InteractSound.Num() > 0)
	{
		int32 index = FMath::RandRange(0, InteractSound.Num() - 1);
		UAudioComponent* audioComp = UGameplayStatics::SpawnSoundAttached(InteractSound[index], RootComponent);

		//reset bInteractOK when Sound Finished.
		if (IsValid(audioComp))
		{
			audioComp->OnAudioFinished.AddDynamic(this, &AAnimal::WhenSoundFinished);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Must Add Animal Sound Assets."));
	}
}

