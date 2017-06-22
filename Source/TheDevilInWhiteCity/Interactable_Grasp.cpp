// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Grasp.h"
#include "GasTrapManager.h"
#include "Interactable_Heater.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractable_Grasp::AInteractable_Grasp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Grasp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Grasp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Grasp::Interact(AActor * a_player)
{

	if(!isPickedUp)
	{
		return;
	}


}

EInteractionType AInteractable_Grasp::GetInteractionType()
{
	if (GasTrapManager && !this->isDone)
	{
		this->isDone = true;

		// cast to
		AGasTrapManager* manager = reinterpret_cast<AGasTrapManager*>(this->GasTrapManager);
		if (manager)
		{
			if (manager->IsDone())
			{
				// play pickup sound
				if (this->PickUpSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, this->PickUpSound, GetActorLocation());
				}

				return EInteractionType::View;
			}
		}
	}

	return EInteractionType::World;
}

void AInteractable_Grasp::OnViewSpace(AActor * a_player)
{
	// call manager function => Despawn
	UStaticMeshComponent* staticMeshComponent = this->FindComponentByClass<UStaticMeshComponent>();
	if (staticMeshComponent)
	{
		if (this->Heater)
		{
			AInteractable_Heater* heater = reinterpret_cast<AInteractable_Heater*>(this->Heater);
			if (heater)
			{
				heater->SetInteract(true);
			}
		}
		//staticMeshComponent->SetVisibility(false);
		
		this->SetActorHiddenInGame(true);
	}
}


