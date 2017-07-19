// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "SoundTrapManager.h"


// Sets default values
ASoundTrapManager::ASoundTrapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASoundTrapManager::Notify(int32 acIndex)
{
	if (onlySolveTrapOnce)
	{
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("ACINDEX: %d"),acIndex);
	//UE_LOG(LogTemp, Warning, TEXT("CURRENT_TRY_INDEX: %d"), CurrentTryIndex);

	if (!CurrentTry.Contains(acIndex))
		CurrentTry[++CurrentTryIndex] = acIndex;

	if (CurrentTryIndex == ActivationOrder.Num() - 1)
	{
		bool isNotEqual = false;

		for (uint8 i = 0; i < 4; i++)
		{
			if (CurrentTry[i] != ActivationOrder[i])
			{
				isNotEqual = true;
			}

			//UE_LOG(LogTemp, Warning, TEXT("=============="));
			//UE_LOG(LogTemp, Warning, TEXT("TryArray: %d"), CurrentTry[i]);
			//UE_LOG(LogTemp, Warning, TEXT("ActivationOrderArray: %d"), ActivationOrder[i]);
			//UE_LOG(LogTemp, Warning, TEXT("=============="));
		}

		
		// solving wasn't successful ==> reset
		CurrentTryIndex = -1;
		for (uint8 i = 0; i < 4; i++)
		{
			CurrentTry[i] = 555;
		}

		if (!isNotEqual)
		{
			UE_LOG(LogTemp, Warning, TEXT("SoundTrapSolved"));
			onlySolveTrapOnce = true;

			// show numbers for player
			ShowBloodNumbers();

			// unlock the door for interacting
			UnlockDoor();
		}
	}


}

void ASoundTrapManager::ShowBloodNumbers()
{
	// unhide actors

	if (this->BloodNumber1)
	{
		this->BloodNumber1->SetActorHiddenInGame(false);
	}

	if (this->BloodNumber2)
	{
		this->BloodNumber2->SetActorHiddenInGame(false);
	}
}

void ASoundTrapManager::UnlockDoor()
{
	if (this->Door)
	{
		// unlock the door
		this->Door->SetLockState(false);
		this->Door->SetSlamState(false);
	}
}

// Called when the game starts or when spawned
void ASoundTrapManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASoundTrapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

