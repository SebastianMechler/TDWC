// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "Interactable_Heater.h"
#include "Interactable_Grasp.h"
//#include "ParticleDefinitions.h"

#include "GasTrapManager.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AGasTrapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGasTrapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float TrapTimer = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Gas = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Mist = nullptr;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	AActor* Player = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AInteractable_Heater* Heater = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AInteractable_Grasp* Grasp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* GraspSpawnTo = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* GasEnds = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UBoxComponent* Collider = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int ExplosionForce = 155000;

	UFUNCTION() 
	void OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void Spawn();

	bool IsDone();



private:
	void SetAudioPlay(bool a_state);

	FVector GraspOrigionalPosition = FVector(0.0f, 0.0f, 0.0f);
	FRotator GraspOrigionalRotation;
	UParticleSystemComponent* GasParticle= nullptr;
	UParticleSystemComponent* MistParticle = nullptr;
	bool isDone = false;
	float timer = -1.0f;
	float deathTimer = -1.0f;
};
