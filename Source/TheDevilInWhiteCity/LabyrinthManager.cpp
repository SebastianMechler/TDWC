// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "LabyrinthManager.h"


// Sets default values
ALabyrinthManager::ALabyrinthManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	if (this->Collider)
	{
		RootComponent = this->Collider;
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ALabyrinthManager::OnTriggerEnter);
	}
}

// Called when the game starts or when spawned
void ALabyrinthManager::BeginPlay()
{
	Super::BeginPlay();

	// open = move up -490
	// close = move down -90


	
	
}

// Called every frame
void ALabyrinthManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!this->IsTriggerdOnce)
	{
		return;
	}

	// how many walls do we have

	for (auto& wall : this->Walls)
	{
		if (!wall.Pointer)
		{
			continue;
		}

		switch (wall.State)
		{
		case EWallState::Close:
			{
				// close = move down -90
				FVector location = wall.Pointer->GetActorLocation();
				location += (MovementDirection * DeltaTime * 100.0f * this->MovementSpeed);

				if (location.Z < UpPositionZ)
				{
					wall.Pointer->SetActorLocation(location);
				}
				else
				{
					location.Z = this->UpPositionZ;
					wall.Pointer->SetActorLocation(location);
				}
			}
			break;
		case EWallState::Open:
			{
				// open = move up -490
				FVector location = wall.Pointer->GetActorLocation();
				location -= (MovementDirection * DeltaTime * 100.0f * this->MovementSpeed);

				if (location.Z > DownPositionZ)
				{
					wall.Pointer->SetActorLocation(location);
				}
				else
				{
					location.Z = this->DownPositionZ;
					wall.Pointer->SetActorLocation(location);
				}
			}
			break;
		default:
			break;
		}
	}
}

void ALabyrinthManager::OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor == Player)
	{
		// start wall movement
		this->IsTriggerdOnce = true;

		//for (auto& wall : this->Walls)
		//{
		//	switch (wall.State)
		//	{
		//	case EWallState::Close:
		//		wall.State = EWallState::Open;
		//		break;
		//	case EWallState::Open:
		//		wall.State = EWallState::Close;
		//		break;
		//	}
		//}
	}
}

