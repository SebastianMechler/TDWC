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
}

// Called to bind functionality to input
void AAPlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AAPlayerController::OnRunBegin);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AAPlayerController::OnRunEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAPlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAPlayerController::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AAPlayerController::MoveForward(float a_value)
{
	if (a_value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), 100.0f * a_value);
	}
}

void AAPlayerController::MoveRight(float a_value)
{
	if (a_value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), 100.0f * a_value);
	}
}

void AAPlayerController::OnRunBegin()
{
	IsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AAPlayerController::OnRunEnd()
{
	IsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

