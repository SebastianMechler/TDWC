// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "SoundTrapManager.h"
#include "Kismet/GameplayStatics.h"


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

	//if (!CurrentTry.Contains(acIndex))
	CurrentTry[++CurrentTryIndex] = acIndex;

	// check each notification for success
	bool isSequenceCorrect = true;
	for (auto i = 0; i < CurrentTryIndex + 1; i++)
	{
		if (CurrentTry[i] != ActivationOrder[i])
		{
			isSequenceCorrect = false;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("IS_SEQ_CORRECT: %d"), isSequenceCorrect);

	if (!isSequenceCorrect)
	{
		CurrentTryIndex = -1;

		// play failure sound
		UE_LOG(LogTemp, Warning, TEXT("SoundTraFailure"));
		if (this->FailureSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, this->FailureSound, GetActorLocation());
		}
	}


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

			// play success sound
			if (this->SuccessSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, this->SuccessSound, GetActorLocation());
			}

			onlySolveTrapOnce = true;

			// show numbers for player
			ShowBloodNumbers();

			// unlock the door for interacting
			UnlockDoor();
		}
		else
		{
			// play failure sound
			UE_LOG(LogTemp, Warning, TEXT("SoundTraFailure"));
			if (this->FailureSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, this->FailureSound, GetActorLocation());
			}
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

