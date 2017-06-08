// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "InteractableExample2.h"


// Sets default values
AInteractableExample2::AInteractableExample2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableExample2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableExample2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->Started)
	{
		return;
	}

	auto newRotation = FMath::Lerp(StartRotation, EndRotation, interpollationTime);
	SetActorRotation(newRotation);

	if (interpollationTime >= 1.0f)
	{
		this->Started = false;
		// fade effect
		// delete bottle
		// ...
	}

	interpollationTime += DeltaTime * DrinkSpeed;
}

void AInteractableExample2::Interact(AActor* a_player)
{
	// do whatever needs to be done for the specific actor, eg a door would open here if the key is in inventory
	// a_player is the actor with all components attached


}

EInteractionType AInteractableExample2::GetInteractionType()
{
	return EInteractionType::View;
}

void AInteractableExample2::OnViewSpace(AActor* a_player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[View interaction Bottle] OnViewSpace..."));

	auto World = this->GetWorld();
	//auto Owner = this->GetActor();

	if (!World || !a_player)
	{
		return;
	}

	UCameraComponent* cameraPtr = a_player->FindComponentByClass<UCameraComponent>();
	if (!cameraPtr)
	{
		return;
	}

	this->Started = true;

	// play drink sound

	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += 90.0f;
	this->EndRotation = NewRotation;

	this->StartRotation = GetActorRotation();

	//World->DestroyActor(Owner);
}


