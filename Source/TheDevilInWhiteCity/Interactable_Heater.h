// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface_Interactable.h"
#include "GameFramework/Actor.h"
#include "Interactable_Heater.generated.h"


UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Heater : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Heater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float lerpTime = 0.0f;
	bool isPickedUp = false;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* GasTrapManager = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Actor_Widget = nullptr;


	void Interact(AActor* a_player) override;
	void OnViewSpace(AActor* a_player) override;
	EInteractionType GetInteractionType() override;

	void SetInteract(bool state);

private:
	bool canInteract = false;
	bool isDone = false;
	
};
