// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable_Door.h"
#include "WallTrapLight.h"
#include "WallTrapManager.generated.h"

USTRUCT()
struct FWallData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AActor* wall;

	FWallData()
		: wall(nullptr)
		, startPosition(FVector(0.0f, 0.0f, 0.0f))
		, endPosition(FVector(0.0f, 0.0f, 0.0f))
	{

	}

	FVector startPosition;
	FVector endPosition;
};

UENUM()
enum class EWallMoveState
{
	None,
	Move
};

UCLASS()
class THEDEVILINWHITECITY_API AWallTrapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallTrapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, Category = "Gameplay")
	//	TArray<AActor*> WallTrapLightActors; // contains all lights

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Player = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AInteractable_Door* Door = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float WallSpeed = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<FWallData> Walls;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UBoxComponent* Collider = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* MoveDistanceObject = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* FaceAngleObject = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float angleDot = 0.55f; // values from 0.0f to 1.0f are good here

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		FVector MoveDirection = FVector(-1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* WallTrapLightActor01 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* WallTrapLightActor02 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* WallTrapLightActor03 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* WallTrapLightActor04 = nullptr;

	UFUNCTION()
		void OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
		void OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	bool IsPlayerWalkingBackwards();
	void SetLightState(bool a_state);

	EWallMoveState WallState = EWallMoveState::None;

	TArray<FVector> WallStartPosition;
	TArray<FVector> WallEndPosition;

	bool onlyOneDoorAction = false;
	bool isRunning = false;
	UCameraComponent* Camera = nullptr;
	UAudioComponent* WallMove = nullptr;

	TArray<AWallTrapLight*> WallTrapLights; // contains all lights
	FVector lastPlayerPos = FVector(0.0f, 0.0f, 0.0f);
};
