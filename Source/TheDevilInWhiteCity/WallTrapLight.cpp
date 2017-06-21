// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "WallTrapLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWallTrapLight::AWallTrapLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	if (this->BoxComponent)
	{
		RootComponent = this->BoxComponent;
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWallTrapLight::OnTriggerEnter);
		BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AWallTrapLight::OnTriggerExit);
	}
}

// Called when the game starts or when spawned
void AWallTrapLight::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Attached Light Component
	auto component = this->GetComponentByClass(ULightComponent::StaticClass());
	if (component)
	{
		auto cmp = reinterpret_cast<ULightComponent*>(component);
		if (cmp)
		{
			this->LightComponent = cmp;
		}
	}
}

// Called every frame
void AWallTrapLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWallTrapLight::OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this->Player && isPlayerFacingBackwards && isActive)
	{
		this->isActive = false;
		// player has entered..
		// shutdown previous light
		if (PreviousLightActor)
		{
			PreviousLightActor->SetActorHiddenInGame(true);
			if (this->HideSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, this->HideSound, PreviousLightActor->GetActorLocation());
			}
		}
	}
}

void AWallTrapLight::OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWallTrapLight::SetLightState(bool a_state)
{
	if (this->LightComponent)
	{
		this->LightComponent->SetVisibility(a_state);
	}
}

void AWallTrapLight::SetPlayerFacing(bool a_isFacingBackwards)
{
	this->isPlayerFacingBackwards = a_isFacingBackwards;
}