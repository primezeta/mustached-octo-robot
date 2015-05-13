// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "prototype.h"
#include "prototypeGameMode.h"
#include "prototypeCharacter.h"

// Set default pawn class to our Blueprinted character
static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScroller/Blueprints/SideScrollerCharacter"));

AprototypeGameMode::AprototypeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScroller/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class == nullptr)
	{
		UE_LOG(CriticalErrors, All, TEXT("AprototypeGameMode: PlayerPawnBPClass.Class is null!"));
	}
	DefaultPawnClass = PlayerPawnBPClass.Class;
}

void AprototypeGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	//Generate the map by creating the first level build trigger (prior to the EnteringMap state)
}

void AprototypeGameMode::LevelBuildTriggerResponse()
{

}