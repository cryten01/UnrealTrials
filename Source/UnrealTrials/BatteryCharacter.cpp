// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCharacter.h"
#include "Pickup.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BatteryPickup.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABatteryCharacter::ABatteryCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.0f);

	// Set a base power level for the character
	InitialPower = 2000.0f;
	CharacterPower = InitialPower;

	// Set the dependence of the speed on the power level
	SpeedFactor = 0.75f;
	BaseSpeed = 10.0f;
}

// Called when the game starts or when spawned
void ABatteryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABatteryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Make a Timer
	CollectPickups();
}

// Called to bind functionality to input
void ABatteryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
}

void ABatteryCharacter::CollectPickups()
{
	// Get all overlapping Actors and store them in an array
	TArray<AActor* > CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// Keep track of the collected battery power
	float CollectedPower = 0;

	// For each Actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast the actor to APickup
		APickup* const TestPickup = Cast<APickup>(CollectedActors[iCollected]);

		// If the cast is successful and the pickup is valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			// Call the pickup's WasCollected function
			TestPickup->WasCollected();
			// Check to see if the pickup is also a battery
			ABatteryPickup* const TestBattery = Cast<ABatteryPickup>(TestPickup);
			if (TestBattery)
			{
				// Increase CollectedPower
				CollectedPower += TestBattery->GetPower();
			}
			// Decativate the pickup
			TestPickup->SetActive(false);
		}
	}

	if (CollectedPower > 0)
	{
		UpdatePower(CollectedPower);
	}
}

float ABatteryCharacter::GetInitialPower()
{
	return InitialPower;
};

float  ABatteryCharacter::GetCurrentPower()
{
	return CharacterPower;
};

/**
* Function to update the character's power.
* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
*/
void  ABatteryCharacter::UpdatePower(float PowerChange)
{
	// Change power
	CharacterPower = CharacterPower + PowerChange;
	// Change speed based on power
	//GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + SpeedFactor * CharacterPower;
	// Call visual effect
	PowerChangeEffect();
};