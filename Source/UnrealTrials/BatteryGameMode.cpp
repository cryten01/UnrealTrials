// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryGameMode.h"


ABatteryGameMode::ABatteryGameMode()
{
	// Sets default pawn class to our blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/UserContent/Blueprints/HeroCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Sets base decay rate
	DecayRate = 0.01f;

	// Sets this actor to call Tick() every frame.  
	PrimaryActorTick.bCanEverTick = true;
}

void ABatteryGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Find all spawn volume actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	// Set play state to playing
	SetCurrentState(EBatteryPlayState::EPlaying);

	// Set the score to beat
	ABatteryCharacter* MyCharacter = Cast<ABatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower()) * 1.25f;
	}
};

void ABatteryGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using the battery collector character
	ABatteryCharacter* MyCharacter = Cast<ABatteryCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// if the character's power is positive
		if (MyCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime * DecayRate*(MyCharacter->GetInitialPower()));
		}
		// when our power is <= 0, set the game's state to EGameOver
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}
	}
}

float ABatteryGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState ABatteryGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ABatteryGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	// handle the new current state
	HandleNewState(CurrentState);
}

void ABatteryGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		// If the games is playing
	case EBatteryPlayState::EPlaying:
	{
		// spawn volumes active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(true);
		}
	}
	break;
	// If we won the game
	case EBatteryPlayState::EWon:
	{
		// spawn volumes inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			//Volume->SetSpawningActive(false);
		}
	}
	break;
	// If we lost the game
	case EBatteryPlayState::EGameOver:
	{
		//// spawn volumes inactive
		//for (ASpawnVolume* Volume : SpawnVolumeActors)
		//{
		//	//Volume->SetSpawningActive(false);
		//}
		//// block player input
		//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		//if (PlayerController)
		//{
		//	PlayerController->SetCinematicMode(true, false, false, true, true);
		//}
		//// ragdoll the character
		//ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		//if (MyCharacter)
		//{
		//	MyCharacter->GetMesh()->SetSimulatePhysics(true);
		//	MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		//}
	}
	break;
	// Unknown default state
	default:
	case EBatteryPlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}


