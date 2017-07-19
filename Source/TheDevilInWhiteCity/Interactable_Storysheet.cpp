// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "Interactable_Storysheet.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractable_Storysheet::AInteractable_Storysheet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractable_Storysheet::BeginPlay()
{
	Super::BeginPlay();
	
	this->OriginalLocation = GetActorLocation();
	this->OriginalRotation = GetActorRotation();

	// get audio component
	auto component = GetComponentByClass(UAudioComponent::StaticClass());
	if (component)
	{
		this->Audio = reinterpret_cast<UAudioComponent*>(component);
		if (this->Audio)
		{
			if (this->TalkSound)
			{
				this->Audio->SetSound(this->TalkSound);
			}
			this->Audio->Stop();
		}
	}
}

// Called every frame
void AInteractable_Storysheet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Storysheet::Interact(AActor* a_player)
{

}

EInteractionType AInteractable_Storysheet::GetInteractionType()
{
	this->OriginalLocation = GetActorLocation();
	this->OriginalRotation = GetActorRotation();

	// play sound
	if (this->InteractionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, this->InteractionSound, GetActorLocation());
	}

	// play talk sound
	if (this->Audio && this->TalkSound)
	{
		if (!this->Audio->IsPlaying())
		{
			this->Audio->Play();
		}
	}

	// update display text
	if (StorysheetManager)
	{
		StorysheetManager->SetText(this->TalkText);
	}

	
	// SHOW MANAGER + CHANGE BLUEPRINT IF
	if (this->StorysheetManager)
	{
		this->StorysheetManager->SetActorHiddenInGame(false);
#ifdef UE_BUILD_DEBUG
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[Interactable_StorySheet]Showing actor..."));
#endif
	}

	return EInteractionType::View;
	//return EInteractionType::World;
}

void AInteractable_Storysheet::OnViewSpace(AActor* a_player)
{
	if (!a_player)
	{
		return;
	}

	SetActorLocation(OriginalLocation);
	SetActorRotation(OriginalRotation);


#ifdef UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("[Interactable_StorySheet]OnViewExit..."));
#endif

	// HIDE MANAGER
	if (this->StorysheetManager)
	{
		this->StorysheetManager->SetActorHiddenInGame(true);
	}

	if (this->Audio && this->TalkSound)
	{
		if (this->Audio->IsPlaying())
		{
			this->Audio->Stop();
		}
	}
}


//auto world = this->GetWorld();
//if (!world)
//{
//	return;
//}

//world->DestroyActor(this);