// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h"
#include "Interactable_Door.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Door : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable_Door();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FRotator startVector;
	FRotator endVector;
	float lerpTime = 0.0f;
	bool interacted = false;
	bool isOpen = false;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float rotationAngleZ = 90.f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float openSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* OpenSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* CloseSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* SlamDoorSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* GasTrapManager = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* LockedDoorSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	bool isLocked = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool isOfficeDoor = false;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetLockState(bool a_state);

	void SetInteractState(bool a_state);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SlamDoor();

	void SetSlamState(bool a_state);

	// Interface functions
	void Interact(AActor* a_player) override;
	EInteractionType GetInteractionType() override;
	void OnViewSpace(AActor* a_player) override;

	bool isSlammed = false;

};
