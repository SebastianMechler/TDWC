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

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float RunSpeed = 1200.0f;

	// State of player
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool IsRunning = false;

	void MoveForward(float a_value);
	void MoveRight(float a_value);
	
	void OnRunBegin();
	void OnRunEnd();

	
};
