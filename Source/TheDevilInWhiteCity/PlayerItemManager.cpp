// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "PlayerItemManager.h"
#include "APlayerController.h"
#include "Interactable.h"

// Sets default values for this component's properties
UPlayerItemManager::UPlayerItemManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerItemManager::BeginPlay()
{
	Super::BeginPlay();

	// Get Pointer to Player's Camera
	AActor* owner = this->GetOwner();

	if (owner)
	{
		// bind action
		owner->InputComponent->BindAction("Run", IE_Pressed, this, &UPlayerItemManager::PerformRaycast);

		// get camera ptr
		auto camera = owner->FindComponentByClass<UCameraComponent>();
		if (camera)
		{
			this->PlayerCamera = camera;
		}
	}
}


// Called every frame
void UPlayerItemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//PerformRaycast();
}

void UPlayerItemManager::PerformRaycast()
{
	if (!this->PlayerCamera)
	{
		return;
	}

	FHitResult result{};
	FVector StartTrace = this->PlayerCamera->GetComponentLocation();
	FVector Direction = this->PlayerCamera->GetForwardVector();
	FVector EndTrace = (Direction * PickupDistance) + StartTrace;

	UWorld* World = GetWorld();
	DrawDebugLine(World, StartTrace, EndTrace, FColor::Red, true);

	if (World && World->LineTraceSingleByChannel(result, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility))
	{
		if (result.Actor->IsA(AInteractable::StaticClass()))
		{
			auto staticMesh = result.Actor->FindComponentByClass<UStaticMeshComponent>();
			if (staticMesh)
			{
				//World->DestroyActor(result.GetActor());
				//staticMesh->SetVectorParameterValueOnMaterials("BaseColor", FVector(1.0f, 0.0f, 0.0f));
				//staticMesh->SetVectorParameterValueOnMaterials("Base Color", FVector(1.0f, 0.0f, 0.0f));
				//staticMesh->SetVectorParameterValueOnMaterials("DiffuseColor", FVector(1.0f, 0.0f, 0.0f));
				//auto material = staticMesh->GetMaterial(0);
				//if (material)d
				//{
				//	
				//}
			}


			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit target: %s"), *result.Actor->GetName()));
		}
	}
}

