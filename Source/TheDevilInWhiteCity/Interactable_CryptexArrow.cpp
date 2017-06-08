// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_CryptexArrow.h"

// Sets default values
AInteractable_CryptexArrow::AInteractable_CryptexArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AInteractable_CryptexArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_CryptexArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto actor = GetAttachParentActor();
	
	if (!actor)
	{
		return;
	}

	this->RootCryptex = reinterpret_cast<ACryptex*>(actor);
}

void AInteractable_CryptexArrow::Interact(AActor* a_player)
{
	if (!RootCryptex)
	{
		return;
	}

	// inform cryptex about pushed button
	RootCryptex->UpdateCryptex(this->Type, this->index);	
}

EInteractionType AInteractable_CryptexArrow::GetInteractionType()
{
	return EInteractionType::World;
}

void AInteractable_CryptexArrow::OnViewSpace(AActor* a_player)
{

}

