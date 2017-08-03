// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Bottle.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Bottle::AInteractable_Bottle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//this->PostProcessVolume = CreateDefaultSubobject<APostProcessVolume>(TEXT("PostProcessVolume01"));

}

// Called when the game starts or when spawned
void AInteractable_Bottle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractable_Bottle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (this->EffectStarted)
	//{
	//	EffectInterpollationTime += DeltaTime * this->EffectFadeInDurationFactor;

	//	float x = FMath::Lerp(0.0f, this->EffectBlurMax, EffectInterpollationTime);
	//	this->PostProcessVolume->Settings.DepthOfFieldFarBlurSize = x;
	//	this->PostProcessVolume->Settings.DepthOfFieldNearBlurSize = x;

	//	if (EffectInterpollationTime >= 1.0f)
	//	{
	//		// Destroy bottle
	//		auto world = this->GetWorld();
	//		if (world)
	//		{
	//			world->DestroyActor(this);
	//		}
	//		this->EffectStarted = false;

	//		// effect ends
	//	}
	//}

	//if (!this->Started)
	//{
	//	return;
	//}

	//auto newRotation = FMath::Lerp(StartRotation, EndRotation, interpollationTime);
	//SetActorRotation(newRotation);

	//if (interpollationTime >= 1.0f)
	//{
	//	this->Started = false;

	//	// start effect
	//	if (this->PostProcessVolume)
	//	{
	//		this->PostProcessVolume->Settings.bOverride_DepthOfFieldMethod = true;
	//		this->PostProcessVolume->Settings.bOverride_DepthOfFieldNearBlurSize = true;
	//		this->PostProcessVolume->Settings.bOverride_DepthOfFieldFarBlurSize = true;
	//		this->EffectStarted = true;
	//		EffectInterpollationTime = 0.0f;


	//		auto meshComponent = this->FindComponentByClass<UStaticMeshComponent>();
	//		if (meshComponent)
	//		{
	//			//meshComponent->bVisible = false;
	//			//meshComponent->bHiddenInGame = true;
	//			meshComponent->ToggleVisibility();
	//		}

	//		//USceneComponent* node = Cast<USceneComponent>(this);
	//		//if (node)
	//		//{
	//		//	node->ToggleVisibility(false);
	//		//}
	//		

	//		
	//		////auto meshComponent = this->GetComponentByClass<>()
	//		//auto meshComponent = this->FindComponentByClass<UStaticMeshComponent>();
	//		//if (meshComponent)
	//		//{
	//		//	meshComponent->bVisible = false;
	//		//	meshComponent->bHiddenInGame = true;
	//		//	//this->PlayerCamera = camera;
	//		//}

	//	}

	//	// fade effect
	//	// delete bottle
	//	// ...
	//}

	//interpollationTime += DeltaTime * DrinkSpeed;
}

void AInteractable_Bottle::Interact(AActor* a_player)
{
	// do whatever needs to be done for the specific actor, eg a door would open here if the key is in inventory
	// a_player is the actor with all components attached

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[View interaction Bottle] WorldInteraction..."));
}

EInteractionType AInteractable_Bottle::GetInteractionType()
{
	return EInteractionType::World;
}

void AInteractable_Bottle::OnViewSpace(AActor* a_player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[View interaction Bottle] OnViewSpace..."));

	//auto World = this->GetWorld();
	////auto Owner = this->GetActor();

	//if (!World || !a_player)
	//{
	//	return;
	//}

	//UCameraComponent* cameraPtr = a_player->FindComponentByClass<UCameraComponent>();
	//if (!cameraPtr)
	//{
	//	return;
	//}

	//this->Started = true;

	//// play drink sounds
	//if (DrinkSound)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, DrinkSound, GetActorLocation());
	//}

	//FRotator NewRotation = GetActorRotation();
	//NewRotation.Pitch += 90.0f;
	//this->EndRotation = NewRotation;

	//this->StartRotation = GetActorRotation();

}
