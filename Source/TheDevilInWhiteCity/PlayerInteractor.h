// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "APlayerController.h"
#include "PlayerInteractor.generated.h"

enum class EInteractionState
{
	ProjectToView,
	InView,
	None,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDEVILINWHITECITY_API UPlayerInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Interaction distance between Camera and Object
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float PickupDistance = 400.0f;

	// reference to Camera
	UCameraComponent* PlayerCamera = nullptr;
	AAPlayerController* PlayerController = nullptr;

	void PerformInteraction();
	void ProjectToView(float DeltaTime);

	EInteractionState CurrentInteractionState = EInteractionState::None; // current state of the interaction process
	AActor* CurrentInteractionObject = nullptr; // current interaction object
	FVector CurrentInteractionViewPoint = FVector(0.0f, 0.0f, 0.0f); // current point the object will move to (infront of camera)
	FVector CurrentInteractionMoveDirection = FVector(0.0f, 0.0f, 0.0f); // direction the interaction object moves (direction to camera view point)
	float InteractionViewPointDistance = 100.0f; // distance which defines the point infront of the camera where the object moves to
	float InteractionViewProjectSpeed = 300.0f; // speed in which the object moves to the camera
	float CurrentInteractionObjectMaxDistance = 0.0f;
	float MaxViewDistance = 10.0f;
	FRotator StartRotation;
	FRotator EndRotation;
};
