// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "APlayerController.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AAPlayerController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	// Normal walking speed
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float WalkSpeed = 600.0f;

	// Running speed
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RunSpeed = 1200.0f;

	// State of player
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool IsRunning = false;

	// Array for footstep sounds	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TArray<USoundBase*> FootstepMap;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float FootstepDistance = 2.0f; // distance the player travels in world to play new sound

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float FootstepRunModifier = 0.8f; // modifier to increase/decrease the speed a footstep will be played when running

	void MoveForward(float a_value);
	void MoveRight(float a_value);

	void LookUp(float a_value);
	void Turn(float a_value);
	
	void OnRunBegin();
	void OnRunEnd();

	void OnLookBackBegin();
	void OnLookBackEnd();

	void SetPaused(bool isPaused);

	void HandleFootstep(float a_deltaTime);
private:
	bool IsPaused = false;
	float CurrentMovement = 0.0f;
	int32_t CurrentFootstepIndex = 0;
	FVector LastFramePosition = FVector(0.0f, 0.0f, 0.0f);
	int lastIdx = -1;
};


//// Camera's rotating speed when moving mouse to look around
//UPROPERTY(EditAnywhere, Category = "Gameplay")
//	float LookSpeed = 30.0f;

//// Min Angle when looking down
//UPROPERTY(EditAnywhere, Category = "Gameplay")
//	float LookUpAngleMin = -80.0f;

//// Max angle when looking up
//UPROPERTY(EditAnywhere, Category = "Gameplay")
//	float LookUpAngleMax = -45.0f;

//void LookUp(float a_value);
//void LookRight(float a_value);

//private:
//float CurrentLookUpValue = 0.0f;
//float CurrentLookRight = 0.0f;