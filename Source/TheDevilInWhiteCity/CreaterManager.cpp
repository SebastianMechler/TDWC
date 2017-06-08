// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "CreaterManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACreaterManager::ACreaterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreaterManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto& e : this->Creaters)
	{
		if (e)
		{
			auto meshComponent = e->FindComponentByClass<UStaticMeshComponent>();
			if (meshComponent)
			{
				meshComponent->SetVisibility(false);
			}
		}
	}

	// create timers
	this->timer = this->ShowDelay + 1.0f;
}

// Called every frame
void ACreaterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->Player == nullptr || this->Creaters.Num() == 0)
	{
		return;
	}

	for (auto& e : this->Creaters)
	{
		float distance = FVector::Distance(e->GetActorLocation(), this->Player->GetActorLocation());

		if (distance < m_hideDistance)
		{
			//if (!this->isHidden)
			{
				this->isHidden = true;
				// hide
				auto meshComponent = e->FindComponentByClass<UStaticMeshComponent>();
				if (meshComponent)
				{
					meshComponent->SetVisibility(false);
				}
			}
		}
	}

	if(this->timer >= 0.0f)
	{
		timer += DeltaTime;
	}

	if (this->timer < ShowDelay)
	{
		return;
	}

	for (auto& e : this->Creaters)
	{
		float distance = FVector::Distance(e->GetActorLocation(), this->Player->GetActorLocation());

		if (distance > m_hideDistance)
		{
			//if (this->isFirst)
			//{
			//	this->isFirst = false;
			//	return;
			//}
			// show
			if (this->isHidden)
			{
				this->timer = 0.0f;

				if (this->Player && this->CreaterShows)
				{
					if(!PlayedAllready)
					{
						UGameplayStatics::PlaySoundAtLocation(this, this->CreaterShows, this->Player->GetActorLocation());
						this->PlayedAllready = true;
					}
				}

				auto meshComponent = e->FindComponentByClass<UStaticMeshComponent>();
				if (meshComponent)
				{
					meshComponent->SetVisibility(true);
				}
			}
		}
		//else
		//{
		//	if (!this->isHidden)
		//	{
		//		this->isHidden = true;
		//		// hide
		//		auto meshComponent = e->FindComponentByClass<UStaticMeshComponent>();
		//		if (meshComponent)
		//		{
		//			meshComponent->SetVisibility(false);
		//		}
		//	}
		//}
	}
}

