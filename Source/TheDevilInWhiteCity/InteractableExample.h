// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "InteractableExample.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractableExample : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()
	
public:	
	AInteractableExample();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* a_player) override; // EXAMPLE ==> implement interface function
	EInteractionType GetInteractionType() override; // EXAMPLE ==> implement interface function
	
};
