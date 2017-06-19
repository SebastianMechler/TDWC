// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "Interactable_LightSwitcher.generated.h"

UENUM()
enum class ELampEffectType
{
	None,
	Flicker,
	Row
};

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_LightSwitcher : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_LightSwitcher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* InteractionSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* FlickerSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* RowSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		ELampEffectType LampEffectType = ELampEffectType::None;


	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float FlickerDuration = 3.0f; // GD

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float FlickerEffectMin = 0.10f; // GD

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float FlickerEffectMax = 0.30f; // GD

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float RowDuration = 3.0f; // GD

	void Interact(AActor* a_player) override; // EXAMPLE ==> implement interface function
	EInteractionType GetInteractionType() override; // EXAMPLE ==> implement interface function
	void OnViewSpace(AActor* a_player) override; // EXAMPLE ==> implement interface function
	
	

private:
	TArray<ULightComponent*> PointLightComponents;


	float FlickerTimer = -1.0f;
	float FlickerEffectTimer = 0.0f;


	
	float RowStep = 0.0f; // RowDuration / LampNum
	float RowStepTimer = 0.0f; // current time
	unsigned int currentLampIndex = 0;

	bool IsRunning = false;
};
