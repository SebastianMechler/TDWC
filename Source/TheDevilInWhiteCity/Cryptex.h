// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CryptexArrowType.h"
#include "Interactable_Door.h"
#include "Cryptex.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API ACryptex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACryptex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateCryptex(ECryptexArrowType a_type, int a_index);
	void TryToSolveCryptex();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<int32> TextSolveValues;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<int32> TextStartValues;



	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UTextRenderComponent* Text01 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UTextRenderComponent* Text02 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UTextRenderComponent* Text03 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UTextRenderComponent* Text04 = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UTextRenderComponent* TextNumbers[4];
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AInteractable_Door* DoorToOpen = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* OpenSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* InteractSoundUp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* InteractSoundDown = nullptr;

private:
	bool IsSolved = false;

};
