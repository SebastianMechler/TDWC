// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Cryptex.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACryptex::ACryptex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CryptexMesh"));
	if (StaticMesh)
	{
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		if (GetRootComponent())
		{
			StaticMesh->SetupAttachment(GetRootComponent());
		}
	}

	//
	// Text01
	//
	this->Text01 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text01"));
	if (Text01)
	{
		Text01->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		if (StaticMesh->GetAttachmentRoot())
		{
			Text01->SetupAttachment(StaticMesh->GetAttachmentRoot());
		}
	}

	this->Text02 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text02"));
	if (Text02)
	{
		Text02->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		if (StaticMesh->GetAttachmentRoot())
		{
			Text02->SetupAttachment(StaticMesh->GetAttachmentRoot());
		}
	}

	this->Text03 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text03"));
	if (Text03)
	{
		Text03->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		if (StaticMesh->GetAttachmentRoot())
		{
			Text03->SetupAttachment(StaticMesh->GetAttachmentRoot());
		}
	}

	this->Text04 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text04"));
	if (Text04)
	{
		Text04->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		if (StaticMesh->GetAttachmentRoot())
		{
			Text04->SetupAttachment(StaticMesh->GetAttachmentRoot());
		}
	}

	// for better indexing
	this->TextNumbers[0] = this->Text01;
	this->TextNumbers[1] = this->Text02;
	this->TextNumbers[2] = this->Text03;
	this->TextNumbers[3] = this->Text04;
}

// Called when the game starts or when spawned
void ACryptex::BeginPlay()
{
	Super::BeginPlay();
	
	// initialize all four text numbers in world
	for (auto i = 0; i < 4; i++)
	{
		this->TextNumbers[i]->SetText(FString::FromInt(this->TextStartValues[i]));
	}

}

// Called every frame
void ACryptex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACryptex::UpdateCryptex(ECryptexArrowType a_type, int a_index)
{
	if (a_index > 3 || a_index < 0 || this->IsSolved)
	{
		// WRONG INDEX OR CRYPTEX IS SOLVED, index ranges from 0 to 3
		return;
	}
	
	auto value = this->TextStartValues[a_index];

	switch (a_type)
	{
	case ECryptexArrowType::Up:
		value++;
		// change number up
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("UP"));
		break;
	case ECryptexArrowType::Down:
		// change number down
		value--;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Down"));
		break;
	default:
		break;
	}

	// no negative and cap to 9
	if (value > 9)
	{
		value = 0;
	}
	else if (value < 0)
	{
		value = 9;
	}

	// assign modified value
	this->TextStartValues[a_index] = value;

	// assign new number
	this->TextNumbers[a_index]->SetText(FString::FromInt(value));

	// check if solved
	this->TryToSolveCryptex();
}

void ACryptex::TryToSolveCryptex()
{
	bool solved = true;

	for (auto i = 0; i < 4; i++)
	{
		if (this->TextStartValues[i] != this->TextSolveValues[i])
		{
			solved = false;
		}
	}

	if (solved)
	{
		// SOLVED YAY
		for (auto i = 0; i < 4; i++)
		{
			this->TextNumbers[i]->SetTextRenderColor(FColor::Green);

			if (this->OpenSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, this->OpenSound, GetActorLocation());
			}

			// TODO: call door script...
			if (DoorToOpen)
			{
				DoorToOpen->SetLockState(false);
			}

		}

		this->IsSolved = true;
	}	
}

