// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interface_Interactable.h" // EXAMPLE => include Interface header
#include "CryptexArrowType.h"
#include "Cryptex.h"
#include "Interactable_CryptexArrow.generated.h"


UCLASS()
class THEDEVILINWHITECITY_API AInteractable_CryptexArrow : public AActor, public IInterface_Interactable // EXAMPLE ==> inherit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_CryptexArrow();

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
		ECryptexArrowType Type = ECryptexArrowType::Up; // what should the arrow do? increase = up, decrease = down

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int index = 0; // index of cryptex (ranges from 0 to 3 ==> 4 numbers)


private:
	ACryptex* RootCryptex = nullptr;
};
