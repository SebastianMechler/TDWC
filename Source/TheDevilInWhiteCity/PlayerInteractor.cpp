// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "PlayerInteractor.h"
#include "Interface_Interactable.h"
#include "InteractableExample.h"

UPlayerInteractor::UPlayerInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractor::BeginPlay()
{
	Super::BeginPlay();

	// Get Pointer to Player's Camera
	AActor* owner = this->GetOwner();
	
	if (owner)
	{
		// bind action
		owner->InputComponent->BindAction("Interact", IE_Pressed, this, &UPlayerInteractor::PerformInteraction);

		// get camera ptr
		AAPlayerController* playerController = reinterpret_cast<AAPlayerController*>(owner);
		if (playerController)
		{
			this->PlayerController = playerController;
		}

		auto camera = owner->FindComponentByClass<UCameraComponent>();
		if (camera)
		{
			this->PlayerCamera = camera;
		}
	}
	
}

void UPlayerInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (CurrentInteractionState)
	{
	case EInteractionState::ProjectToView:
		// Project to view
		ProjectToView(DeltaTime);
		break;
	case EInteractionState::InView:
		// TODO: Allow rotating... ++
		break;
	}
}

void UPlayerInteractor::PerformInteraction()
{
	if (!isEnabled)
	{
		return;
	}

	if (CurrentInteractionState != EInteractionState::None)
	{
		if (CurrentInteractionState == EInteractionState::InView)
		{
			// player cancelled interaction
#ifdef UE_BUILD_DEBUG
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[ViewInteraction] player is done..."));
#endif
			// TODO: add object to inventory
			this->PlayerController->SetPaused(false);
			IInterface_Interactable* base = Cast<IInterface_Interactable>(this->CurrentInteractionObject);
			base->OnViewSpace(GetOwner());

			auto meshComponent = CurrentInteractionObject->FindComponentByClass<UStaticMeshComponent>();
			if (meshComponent)
			{
				meshComponent->SetCollisionEnabled(this->CollisionState);
				meshComponent->SetEnableGravity(true);
			}

			CurrentInteractionState = EInteractionState::None;
			CurrentInteractionObject = nullptr;
			return;
		}

		// object interaction is in process.. dont allow new interaction
		// no new interacting
		return;
	}

	if (!this->PlayerCamera)
	{
		// No Camera is set
#ifdef UE_BUILD_DEBUG
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("UPlayerInteractor::PerformInteraction => NO PLAYER CAMERA"));
#endif
		return;
	}

	FHitResult result{};
	FVector StartTrace = this->PlayerCamera->GetComponentLocation();
	FVector Direction = this->PlayerCamera->GetForwardVector();
	FVector EndTrace = (Direction * PickupDistance) + StartTrace;

	UWorld* World = GetWorld();
	//DrawDebugLine(World, StartTrace, EndTrace, FColor::Red, true);

	if (World && World->LineTraceSingleByChannel(result, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility))
	{
		//if (result.Actor->IsA(AInteractableExample::StaticClass()))
		IInterface_Interactable* base = Cast<IInterface_Interactable>(result.GetActor());
		if (base)
		{
			switch (base->GetInteractionType())
			{
				case EInteractionType::View:
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[ViewInteraction] started..."));
					this->CurrentInteractionState = EInteractionState::ProjectToView;
					this->CurrentInteractionObject = result.GetActor();
					this->CurrentInteractionViewPoint = this->PlayerCamera->GetComponentLocation() + InteractionViewPointDistance * this->PlayerCamera->GetForwardVector();

					this->CurrentInteractionMoveDirection = CurrentInteractionViewPoint - result.GetActor()->GetActorLocation();
					this->CurrentInteractionMoveDirection.Normalize();

					this->CurrentInteractionObjectMaxDistance = FVector::Distance(CurrentInteractionViewPoint, CurrentInteractionObject->GetActorLocation());
					this->CurrentInteractionObjectMaxDistance -= this->MaxViewDistance;

					// start and end rotation
					this->StartRotation = result.GetActor()->GetActorRotation();
					this->EndRotation = FRotationMatrix::MakeFromX(this->CurrentInteractionObject->GetActorLocation() - this->PlayerCamera->GetComponentLocation()).Rotator();

					

					// disable gravity and collision
					auto meshComponent = result.GetActor()->FindComponentByClass<UStaticMeshComponent>();
					if (meshComponent)
					{
						// save collisionstate
						this->CollisionState = meshComponent->GetCollisionEnabled();

						meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						meshComponent->SetEnableGravity(false);
					}

					this->PlayerController->SetPaused(true);
				}
				break;

			case EInteractionType::World:
				base->Interact(GetOwner());
				break;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Hit target: %s"), *result.Actor->GetName()));
		}
	}
}

void UPlayerInteractor::ProjectToView(float DeltaTime)
{
	if (!CurrentInteractionObject)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("UPlayerInteractor::ProjectToView => CurrentInteractionObject is nullptr"));
		return;
	}

	// MaxDistance = 50.0f == 100% - 10.0f
	// CurrentDistance = 40.0f == x == 1 - 0.8f == 0.2f
	// CurrentDistance = 30.0f == x == 1 - 0.6f == 0.4f
	// CurrentDistance = 10.0f == x == 1 - 0.2f == 0.8f
	// 0.0f - 1.0f

	// FMath::Lerp(StartRotation, EndRotation, 1.0f - CurrentDistance / MaxDistance);

	float distance = FVector::Distance(CurrentInteractionViewPoint, CurrentInteractionObject->GetActorLocation());
	if (distance < this->MaxViewDistance)
	{
		// object reached camera view point
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[ViewInteraction] object in view..."));

		//auto PlayerRot = FRotationMatrix::MakeFromX(this->CurrentInteractionObject->GetActorLocation() - this->PlayerCamera->GetComponentLocation()).Rotator();
		//this->CurrentInteractionObject->SetActorRotation(PlayerRot);

		this->CurrentInteractionObject->SetActorRotation(EndRotation);

		CurrentInteractionState = EInteractionState::InView;
	}
	else
	{
		// move object to camera view point
		auto location = CurrentInteractionObject->GetActorLocation();
		location += CurrentInteractionMoveDirection * InteractionViewProjectSpeed * DeltaTime;
		CurrentInteractionObject->SetActorLocation(location);

		auto newRotation = FMath::Lerp(StartRotation, EndRotation, 1.0f - distance / this->CurrentInteractionObjectMaxDistance);
		this->CurrentInteractionObject->SetActorRotation(newRotation);
	}
}

//auto staticMesh = result.Actor->FindComponentByClass<UStaticMeshComponent>();
//if (staticMesh)
//{
//	//World->DestroyActor(result.GetActor());
//	//staticMesh->SetVectorParameterValueOnMaterials("BaseColor", FVector(1.0f, 0.0f, 0.0f));
//	//staticMesh->SetVectorParameterValueOnMaterials("Base Color", FVector(1.0f, 0.0f, 0.0f));
//	//staticMesh->SetVectorParameterValueOnMaterials("DiffuseColor", FVector(1.0f, 0.0f, 0.0f));
//	//auto material = staticMesh->GetMaterial(0);
//	//if (material)d
//	//{
//	//	
//	//}
//}
