// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class UNREALTRIALS_API APickup : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APickup();

	// Returns the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; };

	// Returns whether or not pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
		bool IsActive();

	// Allows other classes to safely change whether or not the pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void SetActive(bool NewPickupState);

	// Function to call when pickup is selected
	UFUNCTION(BlueprintNativeEvent)
		void WasCollected();
	virtual void WasCollected_Implementation();


protected:
	// True if pickup is active, otherwise false
	bool bIsActive;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:	
	// Static mesh thats represents the pickup in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
};
