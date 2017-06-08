// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CreaterManager.generated.h"


UCLASS()
class THEDEVILINWHITECITY_API ACreaterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreaterManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<AActor*> Creaters;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AActor* Player;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	USoundBase* CreaterShows = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float ShowDelay = 60.0f;

	bool isVisible = true;
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float m_hideDistance = 700.0f;


	float timer = -1.0f;
	bool isHidden = false;
	//bool isFirst = true;
};
