// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h"
#include "Interactable_Drawer.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Drawer : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Drawer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector startVector = FVector(0.0f, 0.0f, 0.0f);
	FVector endVector = FVector(0.0f, 0.0f, 0.0f);
	float lerpTime = 0.0f;
	bool interacted = false; 
	bool isOpen = false; 
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float openDistance = 40.f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float openSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* OpenSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* CloseSound = nullptr;

	void Interact(AActor* a_player) override;
	EInteractionType GetInteractionType() override;
	void OnViewSpace(AActor* a_player) override;
	
};
