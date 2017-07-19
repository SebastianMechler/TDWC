// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDevilInWhiteCity.h"
#include "StorysheetManager.h"


// Sets default values
AStorysheetManager::AStorysheetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStorysheetManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStorysheetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FText AStorysheetManager::GetText()
{
	return this->DisplayText;
}

void AStorysheetManager::SetText(FText a_text)
{
	this->DisplayText = a_text;
}
