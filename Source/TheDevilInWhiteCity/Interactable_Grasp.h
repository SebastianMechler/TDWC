// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface_Interactable.h"
#include "GameFramework/Actor.h"
#include "Interactable_Grasp.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Grasp : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Grasp();

protected:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isPickedUp = false;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* PickUpSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* StuckOnSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* GasTrapManager = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AActor* Heater = nullptr;

	void Interact(AActor* a_player) override;
	EInteractionType GetInteractionType() override;
	void OnViewSpace(AActor* a_player) override;

private:
	bool isDone = false;
	
};
