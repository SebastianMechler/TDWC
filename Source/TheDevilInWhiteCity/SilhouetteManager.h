// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable_Door.h"
#include "SilhouetteManager.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API ASilhouetteManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASilhouetteManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UBoxComponent* Collider = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Ghost = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Player = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* MoveGhostTo = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* GhostScreamSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float GhostMovementSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Door = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float SoundDelayTimer = 0.3f;

	UFUNCTION()
		void OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);



private:
	bool TrapTriggered = false;
	bool TrapDone = false;
};
