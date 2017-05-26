// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Tutorial.generated.h"

enum ETutorialStages
{
	Movement,
	Interaction,
	Done
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEDEVILINWHITECITY_API UTutorial : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorial();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float MovementStageDistance = 300.0f; // distance play must travel in order to reach next tutorial stage

	ETutorialStages currentState = Movement;
	float currentDistance = 0.0f;
	FVector lastFramePosition = FVector(0.0f, 0.0f, 0.0f);

};
