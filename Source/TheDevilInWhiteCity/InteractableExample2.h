// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "InteractableExample2.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractableExample2 : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableExample2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* a_player) override; // EXAMPLE ==> implement interface function
	EInteractionType GetInteractionType() override; // EXAMPLE ==> implement interface function
};
