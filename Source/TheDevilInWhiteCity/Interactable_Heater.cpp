// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Heater.h"
#include "GasTrapManager.h"


// Sets default values
AInteractable_Heater::AInteractable_Heater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Heater::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractable_Heater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AInteractable_Heater::Interact(AActor * a_player)
{
	if (!this->GasTrapManager || !canInteract || isDone)
	{
		return;
	}

	this->isDone = true;

	// cast to
	AGasTrapManager* manager = reinterpret_cast<AGasTrapManager*>(this->GasTrapManager);
	if (manager)
	{
		if (manager->IsDone())
		{
			manager->Spawn();
			if (Actor_Widget)
			{
				UStaticMeshComponent* staticMeshComponent = this->Actor_Widget->FindComponentByClass<UStaticMeshComponent>();
				if (staticMeshComponent)
				{
					staticMeshComponent->SetVisibility(false);
				}
			}
		}
	}
}

void AInteractable_Heater::OnViewSpace(AActor * a_player)
{
}

EInteractionType AInteractable_Heater::GetInteractionType()
{
	return EInteractionType::World;
}

void AInteractable_Heater::SetInteract(bool state)
{
	this->canInteract = state;
}


