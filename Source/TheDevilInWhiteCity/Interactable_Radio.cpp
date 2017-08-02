// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Radio.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Radio::AInteractable_Radio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Radio::BeginPlay()
{
	Super::BeginPlay();
	
	auto component = GetComponentByClass(UAudioComponent::StaticClass());
	if (component)
	{
		this->Audio = reinterpret_cast<UAudioComponent*>(component);
		if (this->Audio)
		{
			this->Audio->Stop();
		}
	}

	if (this->Audio && this->TurnOnSound)
	{
		this->Audio->SetSound(this->TurnOnSound);
	}

	// get sound duration
	if (this->TurnOnSound)
	{
		this->Duration = this->TurnOnSound->Duration;
	}
}

// Called every frame
void AInteractable_Radio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->Audio || !this->LoopSound)
	{
		return;
	}

	if (this->IsTurnedOn)
	{
		this->Timer -= DeltaTime;

		if (this->Timer <= 0.0f)
		{
			this->IsTurnedOn = false;

			this->Audio->SetSound(this->LoopSound);
			this->Audio->Play(0.0f);
		}
	}
}

void AInteractable_Radio::Interact(AActor * a_player)
{
	if (!this->Audio || !this->TurnOnSound)
	{
		return;
	}



	if (this->InteractSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, this->InteractSound, GetActorLocation());
	}

	if (this->Audio->IsPlaying())
	{
		this->Audio->Stop();
		this->IsTurnedOn = false;
	}
	else
	{
		if (Manager != nullptr)
			Manager->Notify(Index);

		this->Audio->SetSound(this->TurnOnSound);
		this->Audio->Play(0.0f);

		this->Timer = this->Duration;

		this->IsTurnedOn = true;
	}

}

void AInteractable_Radio::OnViewSpace(AActor* a_player)
{

}

EInteractionType AInteractable_Radio::GetInteractionType()
{
	return EInteractionType::World;
}
