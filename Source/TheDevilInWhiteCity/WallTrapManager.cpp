// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "WallTrapManager.h"


// Sets default values
AWallTrapManager::AWallTrapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	if (this->Collider)
	{
		RootComponent = this->Collider;
		Collider->OnComponentBeginOverlap.AddDynamic(this, &AWallTrapManager::OnTriggerEnter);
		Collider->OnComponentEndOverlap.AddDynamic(this, &AWallTrapManager::OnTriggerExit);
	}

}

// Called when the game starts or when spawned
void AWallTrapManager::BeginPlay()
{
	Super::BeginPlay();

	
	// FUCK YOU UNREAL
	// unreal TArray<AActor*> as UPROPERTY(EditAnywhere, Category="Gameplay") does not work...
	if (this->WallTrapLightActor01)
	{
		this->WallTrapLights.Add(reinterpret_cast<AWallTrapLight*>(WallTrapLightActor01));
	}
	if (this->WallTrapLightActor02)
	{
		this->WallTrapLights.Add(reinterpret_cast<AWallTrapLight*>(WallTrapLightActor02));
	}
	if (this->WallTrapLightActor03)
	{
		this->WallTrapLights.Add(reinterpret_cast<AWallTrapLight*>(WallTrapLightActor03));
	}
	if (this->WallTrapLightActor04)
	{
		this->WallTrapLights.Add(reinterpret_cast<AWallTrapLight*>(WallTrapLightActor04));
	}
		
	// disable all lights
	this->SetLightState(false);

	// hide all WallTrapLights
	for (auto& e : WallTrapLights)
	{
		if (e)
		{
			e->SetActorHiddenInGame(true);
		}
	}

	// obtain all start positions from doors
	for (auto &e : Walls)
	{
		if (e.wall)
		{
			FVector actorLocation = e.wall->GetActorLocation();
			e.startPosition = actorLocation;

			if (this->MoveDistanceObject)
			{
				//actorLocation.Y = MoveDistanceObject->GetActorLocation().Y;
				actorLocation = this->MoveDistanceObject->GetActorLocation();
				actorLocation.Y = 870.0f;
				e.endPosition = actorLocation;
			}
		}
	}

	if (this->Player)
	{
		auto comp = this->Player->GetComponentByClass(UCameraComponent::StaticClass());
		if (comp)
		{
			this->Camera = reinterpret_cast<UCameraComponent*>(comp);
		}
	}

	auto c = this->GetComponentByClass(UAudioComponent::StaticClass());
	if (c)
	{
		this->WallMove = reinterpret_cast<UAudioComponent*>(c);
		if (this->WallMove)
		{
			this->WallMove->Stop();
		}
	}

	if (this->Player)
	{
		this->lastPlayerPos = this->Player->GetActorLocation();
	}
}

// Called every frame
void AWallTrapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool isPlayerFacingBackwards = false;
	bool isPlayerWalkingBackwards = false;

	if (this->Player)
	{
		// get last pos
		FVector currentPlayerPos = this->Player->GetActorLocation();

		// calc direction player moved
		FVector moveDirection = currentPlayerPos - this->lastPlayerPos;
		if (moveDirection.Size() > 0.1f)
		{
			moveDirection.Normalize();

			// dot product to room middle object
			// if facing to him => disable lamps

			//dot product between camera and MoveDistanceObject
			FVector CameraToAngleObject = this->Camera->GetComponentLocation() - this->FaceAngleObject->GetActorLocation();
			CameraToAngleObject.Normalize();
			float dot = FVector::DotProduct(moveDirection, CameraToAngleObject);

			if (dot <= this->angleDot)
			{
//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] player TRUE..."));
//#endif
				isPlayerWalkingBackwards = true;
			}
			else
			{
//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] player FALSE..."));
//#endif
			}

			this->lastPlayerPos = currentPlayerPos;
		}
	}

	if (!this->isRunning || this->WallState == EWallMoveState::None || this->Camera == nullptr || this->MoveDistanceObject == nullptr || !this->FaceAngleObject)
	{
		return;
	}
	
	// MoveDistanceObject
	//dot product between camera and MoveDistanceObject
	FVector CameraToAngleObject = this->Camera->GetComponentLocation() - this->FaceAngleObject->GetActorLocation();
	CameraToAngleObject.Normalize();

	float dot = FVector::DotProduct(this->Camera->GetForwardVector(), CameraToAngleObject);

	bool isMoving = false;

	if (dot >= this->angleDot)
	{
		// inform all lights that the player is facing backwards
		isPlayerFacingBackwards = true;

		// move left
		for (auto &e : Walls)
		{
			// check position...
			// left or right?
			if (e.wall)
			{
				//FVector newPosition = e.wall->GetActorLocation() - e.wall->GetActorForwardVector();
				FVector newPosition = e.wall->GetActorLocation() - (MoveDirection * DeltaTime * 100.0f * this->WallSpeed);
				
//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] -move unblock..."));
//#endif

				if (newPosition.Y > e.startPosition.Y)
				{
					isMoving = true;
					e.wall->SetActorLocation(newPosition);
				}
			}
		}
	}
	else
	{
		// move right (wall to middle of hallway)
		for (auto &e : Walls)
		{

			if (e.wall)
			{
				FVector newPosition = e.wall->GetActorLocation() + (MoveDirection * DeltaTime * 100.0f * this->WallSpeed);
				UE_LOG(LogTemp, Warning, TEXT("CMP: %f < %f"), newPosition.Y, e.endPosition.Y);
//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] move block..."));
//#endif

				if (newPosition.Y < e.endPosition.Y)
				{
					e.wall->SetActorLocation(newPosition);
					isMoving = true;
				}
			}
		}
	}

	bool enabled = isPlayerFacingBackwards && isPlayerWalkingBackwards;
	for (auto& e : WallTrapLights)
	{
		if (e)
		{
			e->SetPlayerFacing(enabled);
		}
	}


	// WallMoveComponent assigned?
	if (this->WallMove)
	{
		// are we not moving?
		if (!isMoving || !this->isRunning)
		{
			// stop sound
			this->WallMove->Stop();
		}
		else
		{
			// we are moving, but is currently no sound beeing played?
			if (!this->WallMove->IsPlaying())
			{
				// play sound
				this->WallMove->Play();
			}
		}
	}
}

void AWallTrapManager::OnTriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor == this->Player)
	{
		this->isRunning = true;
		this->WallState = EWallMoveState::Move;

		if(this->Door && !this->onlyOneDoorAction)
		{
			this->Door->SlamDoor();
			this->onlyOneDoorAction = true;
		}

		// unhide all walltraplights
		for (auto& e : WallTrapLights)
		{
			if (e)
			{
				e->SetActorHiddenInGame(false);
				e->isActive = true;
			}
		}

		// enable all lights
		this->SetLightState(true);

		// TODO: MAYBE PLAY SOME SOUND FOR ENABLING ALL LIGHTS AT ONCE?
				
	}
}

void AWallTrapManager::OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this->Player)
	{
		this->isRunning = false;

		if (this->WallMove)
		{
			this->WallMove->Stop();
		}

		for (auto& e : WallTrapLights)
		{
			if (e)
			{
				e->isActive = false;
			}
		}
	}
}

void AWallTrapManager::SetLightState(bool a_state)
{
	// enable all lights
	for (auto& e : WallTrapLights)
	{
		if (e)
		{
			#ifdef UE_BUILD_DEBUG
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] enabling light..."));
			#endif
			// TODO: MAYBE PLAY SOME SOUND FOR ENABLING ALL LIGHTS AT ONCE?
			e->SetLightState(a_state);
		}
	}
}

bool AWallTrapManager::IsPlayerWalkingBackwards()
{
	// DO NOT USE THIS....
	if (this->Player)
	{
		// get last pos
		FVector currentPlayerPos = this->Player->GetActorLocation();

		// calc direction player moved
		FVector moveDirection = currentPlayerPos - this->lastPlayerPos;
		if (moveDirection.Size() > 0.1f)
		{
			moveDirection.Normalize();

			// dot product to room middle object
			// if facing to him => disable lamps

			//dot product between camera and MoveDistanceObject
			FVector CameraToAngleObject = this->Camera->GetComponentLocation() - this->FaceAngleObject->GetActorLocation();
			CameraToAngleObject.Normalize();
			float dot = FVector::DotProduct(moveDirection, CameraToAngleObject);

			if (dot <= this->angleDot)
			{
#ifdef UE_BUILD_DEBUG
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] player TRUE..."));
#endif
				return true;
			}
			else
			{
#ifdef UE_BUILD_DEBUG
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[WallTrap] player FALSE..."));
#endif
				return false;
			}

			this->lastPlayerPos = currentPlayerPos;
		}
	}
	return false;
}