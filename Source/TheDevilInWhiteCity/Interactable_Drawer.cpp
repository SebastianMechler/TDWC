// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Drawer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Drawer::AInteractable_Drawer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Drawer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Drawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!interacted)
	{
		return;
	}

	// 0.016f
	lerpTime += DeltaTime * openSpeed;

	// 0.0f - 1.0f
	FVector newPosition = FMath::Lerp(startVector, endVector, lerpTime);

	SetActorLocation(newPosition);

	if(lerpTime > 1)
	{
		interacted = false;
		endVector = FVector(0.0f, 0.0f, 0.0f);
	}
}

void AInteractable_Drawer::Interact(AActor * a_player)
{
	//auto headscale = this->GetParentActor()->GetActorTransform().GetScale3D()
	auto head = this->GetAttachParentActor();

	if(head == nullptr)
	{
		return;
	}

	if (endVector != FVector::ZeroVector)
	{
		return;
	}

	FVector headFowardVector = head->GetActorRightVector();
	startVector = this->GetActorLocation();

	if(!isOpen)
	{
		endVector = startVector + headFowardVector * openDistance;
		isOpen = true;
		if (OpenSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
		}
	}
	else
	{
		endVector = startVector - headFowardVector * openDistance;
		isOpen = false;
		if (CloseSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());
		}
	}

	lerpTime = 0.0f;
	interacted = true; 
	
}

EInteractionType AInteractable_Drawer::GetInteractionType()
{
	return EInteractionType::World;
}
void AInteractable_Drawer::OnViewSpace(AActor* a_player)
{

}


