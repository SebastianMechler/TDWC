// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WallTrapLight.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AWallTrapLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallTrapLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* Player = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AActor* PreviousLightActor = nullptr;

	UPROPERTY(EditAnywhere, Category ="Gameplay")
	UBoxComponent* BoxComponent = nullptr; // read only

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* HideSound = nullptr;

	UFUNCTION()
		void OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetLightState(bool a_state);
	void SetPlayerFacing(bool a_isFacingBackwards);

	bool isActive = false;
private:
	ULightComponent* LightComponent = nullptr;
	bool isPlayerFacingBackwards = false;
};
