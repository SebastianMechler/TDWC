// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Key.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Key::AInteractable_Key()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Key::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Key::Interact(AActor* a_player)
{

}

EInteractionType AInteractable_Key::GetInteractionType()
{
	return EInteractionType::View;
}

void AInteractable_Key::OnViewSpace(AActor* a_player)
{
	if (this->Door)
	{
		this->Door->SetLockState(false);

		if (this->DoorHintSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, this->DoorHintSound, GetActorLocation());
		}

	}

	this->Destroy();
	//this->DestroyActor();
}