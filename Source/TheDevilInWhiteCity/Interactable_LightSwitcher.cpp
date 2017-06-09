// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_LightSwitcher.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_LightSwitcher::AInteractable_LightSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_LightSwitcher::BeginPlay()
{
	Super::BeginPlay();
	
	// get reference to point light component
	auto components = this->GetComponentsByClass(UPointLightComponent::StaticClass());

	for (auto& e : components)
	{
		if (e)
		{
			this->PointLightComponents.Add(reinterpret_cast<UPointLightComponent*>(e));
		}
	}
}

// Called every frame
void AInteractable_LightSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (this->LampEffectType)
	{
	case ELampEffectType::Flicker:
		{
			if (this->FlickerTimer > 0.0f)
			{
				this->FlickerEffectTimer -= DeltaTime;

				if (this->FlickerEffectTimer < 0.0f)
				{
					//this->FlickerEffectTimer = this->FlickerEffect;
					this->FlickerEffectTimer = FMath::RandRange(this->FlickerEffectMin, this->FlickerEffectMax);

					for (auto& e : this->PointLightComponents)
					{
						if (e)
						{
							// flicker
							e->ToggleVisibility();

							// play sound
							if (this->FlickerSound)
							{
								UGameplayStatics::PlaySoundAtLocation(this, this->FlickerSound, e->GetComponentLocation());
							}
						}
					}
				}

				this->FlickerTimer -= DeltaTime;

				// enable lights
				if (this->FlickerTimer < 0.0f)
				{
					// END
					for (auto& e : this->PointLightComponents)
					{
						if (e)
						{
							e->SetVisibility(true);
						}
					}
				}
			}
		}
		break;
	case ELampEffectType::Row:
	{
		if (this->IsRunning)
		{
			this->RowStepTimer -= DeltaTime;

			if (RowStepTimer < 0.0f)
			{
				// turn on one lamp/light
				auto element = this->PointLightComponents[this->currentLampIndex];
				if (element)
				{
					element->ToggleVisibility();
				}

				// play sound
				if (this->RowSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, this->RowSound, element->GetComponentLocation());
				}

				// reset rowstep timer
				this->RowStepTimer = RowStep;

				// end reached?
				if (this->currentLampIndex == this->PointLightComponents.Num() - 1)
				{
					this->currentLampIndex = 0;
					this->IsRunning = false;
				}
				else
				{
					this->currentLampIndex++;
				}

			}
		}
	}
		break;
	}
	
}

void AInteractable_LightSwitcher::Interact(AActor* a_player)
{
	switch (this->LampEffectType)
	{
	case ELampEffectType::Flicker:
		if (this->FlickerTimer == -1.0f)
		{
			this->FlickerTimer = this->FlickerDuration;
			this->FlickerEffectTimer = FMath::RandRange(this->FlickerEffectMin, this->FlickerEffectMax);
			//this->FlickerEffectTimer = this->FlickerEffect;
		}
		break;
	case ELampEffectType::None:
		for (auto& e : this->PointLightComponents)
		{
			if (e)
			{
				e->ToggleVisibility();
			}
		}
		break;
	case ELampEffectType::Row:

		if (!this->IsRunning)
		{
			this->IsRunning = true;

			if (PointLightComponents.Num() > 0)
			{
				this->RowStep = this->RowDuration / PointLightComponents.Num();
				this->RowStepTimer = RowStep;
			}
		}
		break;
	}

	if (this->PointLightComponents.Num() > 0)
	{
		// play sound
		if (this->InteractionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, this->InteractionSound, GetActorLocation());
		}
	}


}
EInteractionType AInteractable_LightSwitcher::GetInteractionType()
{
	return EInteractionType::World;
}
void AInteractable_LightSwitcher::OnViewSpace(AActor* a_player)
{

}

