// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interface_Interactable.generated.h"

enum class EInteractionType
{
	World,
	View
};

UINTERFACE(Blueprintable, MinimalAPI)
class UInterface_Interactable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IInterface_Interactable
{
	GENERATED_IINTERFACE_BODY()
public:
	
	virtual void Interact(AActor* a_player) = 0;
	virtual EInteractionType GetInteractionType() = 0;
};