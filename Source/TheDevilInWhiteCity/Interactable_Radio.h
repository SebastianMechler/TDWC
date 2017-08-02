// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h"
#include "SoundTrapManager.h"
#include "Interactable_Radio.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Radio : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Radio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Blueprintcallable, Category ="Gameplay")
	void Interact(AActor* a_player) override;
	void OnViewSpace(AActor* a_player) override;
	EInteractionType GetInteractionType() override;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* InteractSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 Index;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		ASoundTrapManager* Manager = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* LoopSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* TurnOnSound = nullptr;


private:
	UAudioComponent* Audio = nullptr;
	float Duration = 0.0f;
	float Timer = 0.0f;
	bool IsTurnedOn = false;
};
