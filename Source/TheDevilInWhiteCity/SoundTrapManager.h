// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable_Door.h"
#include "SoundTrapManager.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API ASoundTrapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundTrapManager();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<int32> ActivationOrder;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<int32> CurrentTry;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* BloodNumber1 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* BloodNumber2 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AInteractable_Door* Door = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* SuccessSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* FailureSound = nullptr;

	void Notify(int32 acIndex);

private:
	int32 CurrentTryIndex = -1;
	bool onlySolveTrapOnce = false;

	void ShowBloodNumbers();
	void UnlockDoor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
