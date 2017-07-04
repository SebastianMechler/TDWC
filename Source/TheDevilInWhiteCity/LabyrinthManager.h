// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LabyrinthManager.generated.h"


UENUM()
enum class EWallState
{
	Open, 
	Close
};


USTRUCT()
struct FWall
{
	GENERATED_BODY()

	FWall()
		: State(EWallState::Close)
		, Pointer(nullptr)
	{
	}

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AActor* Pointer;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	EWallState State = EWallState::Close;

};

UCLASS()
class THEDEVILINWHITECITY_API ALabyrinthManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabyrinthManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public: 
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	TArray <FWall> Walls; 	
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	AActor* Player = nullptr; 

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	UBoxComponent* Collider = nullptr; 

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float DownPositionZ = -90.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float UpPositionZ = 290.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float MovementSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* MovementSound = nullptr;

private:
	FVector MovementDirection = FVector(0.0f, 0.0f, 1.0f);
	bool IsTriggerdOnce = false;
};
