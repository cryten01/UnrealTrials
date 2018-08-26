// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "UnrealTrials.h"

// Sets default values for this actor's properties
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(false);

	// Sets base power level of battery
	BatteryPower = 150.0f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	// Use the base pickup behaviour
	Super::WasCollected_Implementation();

	// Destroys the battery
	Destroy();
}

float ABatteryPickup::GetPower()
{
	return BatteryPower;
}


