// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "GasTrapManager.h"
#include "APlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGasTrapManager::AGasTrapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));	
	RootComponent = this->Collider;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGasTrapManager::OnTriggerEnter);
	

	//Gas ParticleSystem Create
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/TDWC-master/Content/Paticles/P_Dampf.P_Dampf'"));
	//PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	//PSC->SetTemplate(PS.Object);
}

// Called when the game starts or when spawned
void AGasTrapManager::BeginPlay()
{
	Super::BeginPlay();

	auto comp = this->GetComponentByClass(UAudioComponent::StaticClass());
	if (comp)
	{
		this->GasLeak = reinterpret_cast<UAudioComponent*>(comp);
	}


	if (this->Gas)
	{
		this->GasParticle = reinterpret_cast<UParticleSystemComponent*>(this->Gas->GetComponentByClass(UParticleSystemComponent::StaticClass()));
	}

	if (this->Mist )
	{
		this->MistParticle = reinterpret_cast<UParticleSystemComponent*>(this->Mist->GetComponentByClass(UParticleSystemComponent::StaticClass()));
	}

	if(this->MistParticle)
	{
		this->MistParticle->DeactivateSystem();
		this->MistParticle->SetVisibility(false);
	}

	if (this->GasParticle)
	{
		this->GasParticle->SetVisibility(false);
		this->GasParticle->DeactivateSystem();
	}

}

// Called every frame
void AGasTrapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (timer >= 0.0f)
	{
		this->timer += DeltaTime;

		if(timer >= TrapTimer)
		{
			timer = -1.0f;

			if (this->GasEnds)
			{
				UGameplayStatics::PlaySoundAtLocation(this, GasEnds, GetActorLocation());
			}
		}

	}

}

void AGasTrapManager::OnTriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this->Player && isDone == false)
	{
#ifdef UE_BUILD_DEBUG
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ENTER.."));
#endif
		isDone = true;

		this->timer = 0.0f;

		// set spawn position
		if(this->GasParticle)
		{
			this->GasParticle->SetVisibility(true);
			this->GasParticle->ActivateSystem();
		}

		if (this->MistParticle)
		{
			this->MistParticle->SetVisibility(true);
			this->MistParticle->ActivateSystem();
		}

		//if(this->GasStarts)
		//{
		//	//UGameplayStatics::PlaySoundAtLocation(this, GasStarts, GetActorLocation());
		//}
		
		if (this->GasLeak)
		{
			this->GasLeak->Play();
		}

		if (this->Grasp && this->GraspSpawnTo)
		{
			// store current location
			this->GraspOrigionalPosition = this->Grasp->GetActorLocation();
			this->GraspOrigionalRotation = this->Grasp->GetActorRotation();

			this->Grasp->SetActorLocation(this->GraspSpawnTo->GetActorLocation());
		}
	}

}

void AGasTrapManager::Spawn()
{
	if (this->Grasp)
	{
		this->Grasp->SetActorLocation(this->GraspOrigionalPosition);
		this->Grasp->SetActorRotation(this->GraspOrigionalRotation);

		UStaticMeshComponent* staticMeshComponent = this->Grasp->FindComponentByClass<UStaticMeshComponent>();
		if (staticMeshComponent)
		{
			staticMeshComponent->SetVisibility(true);
		}
	}

	if (this->MistParticle)
	{
		this->MistParticle->DeactivateSystem();
		this->MistParticle->SetVisibility(false);
	}

	if (this->GasParticle)
	{
		this->GasParticle->SetVisibility(false);
		this->GasParticle->DeactivateSystem();
	}

	if (this->GasEnds)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GasEnds, GetActorLocation());
	}

	if (this->GasLeak)
	{
		this->GasLeak->Stop();
	}

	this->timer = -1.0f;
}

bool AGasTrapManager::IsDone()
{
	return this->isDone;
}