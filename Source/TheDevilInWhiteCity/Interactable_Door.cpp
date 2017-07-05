// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Door.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Door::AInteractable_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractable_Door::BeginPlay()
{
	Super::BeginPlay();

	// start rotation
	this->startVector = GetActorRotation();
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

			if (this->isSlammed)
			{
				this->isLocked = true;
			}
	}
}

void AInteractable_Door::Interact(AActor * a_player)
{
	if (this->isLocked)
	{
		// TODO: error sound locked
		if (this->LockedDoorSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, this->LockedDoorSound, GetActorLocation());
		}
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
		tmp.Yaw += this->rotationAngleZ;
		this->endVector = tmp;

		isOpen = true;

		if (this->isSlammed)
		{
			if (this->SlamDoorSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SlamDoorSound, GetActorLocation());
			}
		}
		else
		{
			if (OpenSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
			}
		}
		
	}
	else
	{
		this->endVector = GetActorRotation();

		isOpen = false;
		if (this->isSlammed)
		{
			if (this->SlamDoorSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SlamDoorSound, GetActorLocation());
			}
		}
		else
		{
			if (OpenSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
			}
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

void AInteractable_Door::SetInteractState(bool a_state)
{
	this->interacted = a_state;
}

void AInteractable_Door::SlamDoor()
{
	this->isLocked = false;
	this->isSlammed = true;
	this->interacted = false; 
	this->Interact(nullptr);
}
