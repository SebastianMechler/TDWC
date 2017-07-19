// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "StorysheetManager.h"
#include "Interactable_Storysheet.generated.h"

UCLASS()
class THEDEVILINWHITECITY_API AInteractable_Storysheet : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Storysheet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* a_player) override; // EXAMPLE ==> implement interface function
	EInteractionType GetInteractionType() override; // EXAMPLE ==> implement interface function
	void OnViewSpace(AActor* a_player) override;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* InteractionSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		USoundBase* TalkSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UAudioComponent* Audio = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		FText TalkText;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		AStorysheetManager* StorysheetManager = nullptr;
private:
	FVector OriginalLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator OriginalRotation;


};
