// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "SilhouetteManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASilhouetteManager::ASilhouetteManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	if (this->Collider)
	{
		RootComponent = this->Collider;
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ASilhouetteManager::OnTriggerEnter);
	}

}

// Called when the game starts or when spawned
void ASilhouetteManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASilhouetteManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->TrapTriggered && !this->TrapDone)
	{
		// check sound
		if (this->SoundDelayTimer > 0.0f)
		{
			this->SoundDelayTimer -= DeltaTime;
			if (this->SoundDelayTimer <= 0.0f)
			{
				// play sound
				if (this->GhostScreamSound)
				{
					if (this->Ghost)
					{
						UGameplayStatics::PlaySoundAtLocation(this, this->GhostScreamSound, this->Ghost->GetActorLocation());
					}
				}
				this->SoundDelayTimer = -1.0f;
			}
		}

		// move ghost
		if (this->Ghost && this->MoveGhostTo)
		{
			FVector newGhostLocation = this->Ghost->GetActorLocation();

			// set new position
			newGhostLocation.Y -= this->GhostMovementSpeed * 100.0f * DeltaTime;

			// -600 start
			// -1500 end

			FVector ghostLocation = this->MoveGhostTo->GetActorLocation();

			if (ghostLocation.Y >= newGhostLocation.Y)
			{
				if (this->Door)
				{
					auto d = reinterpret_cast<AInteractable_Door*>(this->Door);
					if (d)
					{
						d->SlamDoor();
					}
				}
				this->TrapDone = true;
				this->Ghost->SetActorHiddenInGame(true);
			}
			else
			{
//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[GhostTrap] Moving ghost..."));
//#endif
				// move ghost
				this->Ghost->SetActorLocation(newGhostLocation);
			}
			
		}
	}

}

void ASilhouetteManager::OnTriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this->Player && !this->TrapTriggered)
	{
		this->TrapTriggered = true;

		//if (this->GhostScreamSound)
		//{
		//	if (this->Ghost)
		//	{
		//		UGameplayStatics::PlaySoundAtLocation(this, this->GhostScreamSound, this->Ghost->GetActorLocation());
		//	}
		//}

//#ifdef UE_BUILD_DEBUG
//				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[GhostTrap] triggered..."));
//#endif
		// play SCREAM


	}
}
