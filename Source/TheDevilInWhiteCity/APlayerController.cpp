// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "APlayerController.h"


// Sets default values
AAPlayerController::AAPlayerController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (CurrentLookUpValue != 0.0f)
	//{
	//	// rotate Camera around Y-Axis
	//	FRotator NewRotation = FirstPersonCameraComponent->GetComponentRotation();
	//	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CurrentLookUpValue * DeltaTime * 10.0f * LookSpeed, LookUpAngleMin, LookUpAngleMax);
	//	FirstPersonCameraComponent->SetWorldRotation(NewRotation);
	//	CurrentLookUpValue = 0.0f;
	//}

	//if (CurrentLookRight != 0.0f)
	//{
	//	// rotate camera around Z-Axis
	//	
	//	//FRotator NewRotation = FirstPersonCameraComponent->GetComponentRotation();
	//	//NewRotation.Yaw += CurrentLookRight * DeltaTime * 10.0f * LookSpeed;
	//	//FirstPersonCameraComponent->SetWorldRotation(NewRotation);
	//	//CurrentLookUpValue = 0.0f;
	//}
}

// Called to bind functionality to input
void AAPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AAPlayerController::OnRunBegin);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AAPlayerController::OnRunEnd);
	PlayerInputComponent->BindAction("LookBack", IE_Pressed, this, &AAPlayerController::OnLookBackBegin);
	PlayerInputComponent->BindAction("LookBack", IE_Released, this, &AAPlayerController::OnLookBackEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAPlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAPlayerController::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AAPlayerController::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AAPlayerController::LookUp);
}

void AAPlayerController::MoveForward(float a_value)
{
	if (!IsPaused && a_value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), a_value);
	}
}

void AAPlayerController::MoveRight(float a_value)
{
	if (!IsPaused && a_value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), a_value);
	}
}

void AAPlayerController::LookUp(float a_value)
{
	if (!IsPaused)
	{
		this->AddControllerPitchInput(a_value);
	}
}

void AAPlayerController::Turn(float a_value)
{
	if (!IsPaused)
	{
		this->AddControllerYawInput(a_value);
	}
}

void AAPlayerController::OnRunBegin()
{
	if (!IsPaused)
	{
		IsRunning = true;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AAPlayerController::OnRunEnd()
{
	if (!IsPaused)
	{
		IsRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AAPlayerController::OnLookBackBegin()
{
	if (!IsPaused)
	{
		FirstPersonCameraComponent->bUsePawnControlRotation = false;
		FRotator NewRotation = FirstPersonCameraComponent->GetComponentRotation();
		NewRotation.Yaw -= 180.0f;
		FirstPersonCameraComponent->SetWorldRotation(NewRotation);
	}
}

void AAPlayerController::OnLookBackEnd()
{
	if (!IsPaused)
	{
		FRotator NewRotation = FirstPersonCameraComponent->GetComponentRotation();
		NewRotation.Yaw += 180.0f;
		FirstPersonCameraComponent->SetWorldRotation(NewRotation);

		FirstPersonCameraComponent->bUsePawnControlRotation = true;
	}
}

void AAPlayerController::SetPaused(bool isPaused)
{
	this->IsPaused = isPaused;
}