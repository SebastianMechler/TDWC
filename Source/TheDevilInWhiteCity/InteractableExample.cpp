// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "InteractableExample.h"


// Sets default values
AInteractableExample::AInteractableExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableExample::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void AInteractableExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableExample::Interact(AActor* a_player)
{
	// do whatever needs to be done for the specific actor, eg a door would open here if the key is in inventory
	// a_player is the actor with all components attached
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("[WorldInteraction] Interacting..."));

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 60.0f;
	SetActorRotation(NewRotation);
}

EInteractionType AInteractableExample::GetInteractionType()
{
	return EInteractionType::World;
}

void AInteractableExample::OnViewSpace(AActor* a_player)
{

}

