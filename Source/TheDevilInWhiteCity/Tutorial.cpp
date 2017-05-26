// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Tutorial.h"


// Sets default values for this component's properties
UTutorial::UTutorial()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTutorial::BeginPlay()
{
	Super::BeginPlay();

	this->lastFramePosition = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UTutorial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (this->currentState)
	{
	case ETutorialStages::Movement:
		this->currentDistance += (this->GetOwner()->GetActorLocation() - this->lastFramePosition).Size();
		this->lastFramePosition = this->GetOwner()->GetActorLocation();

		if (currentDistance >= MovementStageDistance)
		{
			int32 tmp = (int32)this->currentState;
			tmp++;
			this->currentState = (ETutorialStages)tmp;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Movement Stage done..."));
		}

		break;
	default:
		break;
	}

	// ...
}

