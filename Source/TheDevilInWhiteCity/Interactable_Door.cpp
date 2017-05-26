// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Door.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Door::AInteractable_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// start rotation
	this->startVector = GetActorRotation();

}

// Called when the game starts or when spawned
void AInteractable_Door::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractable_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!interacted)
	{
		return;
	}

	// 0.016f
	lerpTime += DeltaTime * openSpeed;

	if (this->isOpen)
	{
		// is being opened
		FRotator newRotation = FMath::Lerp(this->startVector, this->endVector, this->lerpTime);
		SetActorRotation(newRotation);
	}
	else
	{
		// is being closed
		FRotator newRotation = FMath::Lerp(this->endVector, this->startVector, this->lerpTime);
		SetActorRotation(newRotation);
	}

	if (lerpTime > 1.0f)
	{
		interacted = false;
	}
}

void AInteractable_Door::Interact(AActor * a_player)
{
	if (this->isLocked)
	{
		// TODO: error sound locked
		return;
	}

	if (this->interacted)
	{
		return;
	}

	if (!isOpen)
	{
		// get end rotation for opening
		FRotator tmp = startVector;
		tmp.Yaw += 90.0f;
		this->endVector = tmp;

		isOpen = true;
		if (OpenSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		}
	}
	else
	{
		this->endVector = GetActorRotation();

		isOpen = false;
		if (CloseSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());
		}
	}

	lerpTime = 0.0f;
	interacted = true;

}

EInteractionType AInteractable_Door::GetInteractionType()
{
	return EInteractionType::World;
}
void AInteractable_Door::OnViewSpace(AActor* a_player)
{

}

void AInteractable_Door::SetLockState(bool a_state)
{
	this->isLocked = a_state;
}