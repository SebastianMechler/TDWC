// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "Interactable_Bottle.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Bottle : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable_Bottle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* a_player) override; // EXAMPLE ==> implement interface function
	EInteractionType GetInteractionType() override; // EXAMPLE ==> implement interface function
	void OnViewSpace(AActor* a_player) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float DrinkSpeed = 1.5f; // value which determines how fast the player will drink the bottle (1.5f is good here)

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	APostProcessVolume* PostProcessVolume = nullptr; // object to select which posteffect will be modified

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float EffectFadeInDurationFactor = 0.2f; // value between 0.0 and 1.0f determining how fast the blur-effect will fade in

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* DrinkSound = nullptr;

private:
	bool Started = false;
	FRotator StartRotation;
	FRotator EndRotation;
	float interpollationTime = 0.0f;
	
	bool EffectStarted = false;
	float EffectInterpollationTime = 0.0f;
	float EffectBlurMax = 15.0f;
	
};
