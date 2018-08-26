// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BatteryCharacter.generated.h"

UCLASS()
class UNREALTRIALS_API ABatteryCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CollectionSphere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;

public:
	// Sets default values for this character's properties
	ABatteryCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CollectionSphere subobject **/
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }

	/** Accessor function for initial power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetInitialPower();

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetCurrentPower();

	/**
	* Function to update the character's power.
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdatePower(float PowerChange);



protected:
	// Starting power level of our character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float InitialPower;

	// Multiplier for character speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float SpeedFactor;

	// Speed when power level = 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
		float BaseSpeed;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when we press a key any pickups inside the CollectionSphere
	UFUNCTION(BlueprintCallable, Category = "Pickups")
		void CollectPickups();

	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
	void PowerChangeEffect();



private:
	// Current power level of our character
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float CharacterPower;

};
