// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BatteryCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SpawnVolume.h"
#include "GameFramework/PawnMovementComponent.h"
#include "UnrealTrials.h"

#include "BatteryGameMode.generated.h"


// Enum to store the current state of gameplay
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

/**
 * 
 */
UCLASS()
class UNREALTRIALS_API ABatteryGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABatteryGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Returns power needed to win - needed for the HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	// Returns the current playing state
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	// Sets a new playing state
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// The rate at which the character loses power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	// The power needed to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

private:
	// The current state of the game
	EBatteryPlayState CurrentState;

	// All SpawnVolumes in the game
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	// Handle any function calls that rely upon changing the playing state of our game
	void HandleNewState(EBatteryPlayState NewState);
};
