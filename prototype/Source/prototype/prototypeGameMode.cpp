// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "prototype.h"
#include "prototypeGameMode.h"
#include "prototypeCharacter.h"

AprototypeGameMode::AprototypeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScroller/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class == nullptr)
	{
		UE_LOG(CriticalErrors, All, TEXT("AprototypeGameMode: PlayerPawnBPClass.Class is null!"));
	}

	//static ConstructorHelpers::FObjectFinder<ATriggerBox> BasicTileBPClass(TEXT("Blueprint'/Game/SideScroller/Blueprints/TriggerBox_BasicTile_Blueprint.TriggerBox_BasicTile_Blueprint'"));
	static ConstructorHelpers::FClassFinder<ATriggerBox> BasicTileBPClass(TEXT("Blueprint'/Game/SideScroller/Blueprints/TriggerBox_BasicTile_Blueprint'"));
	if (BasicTileBPClass.Class == nullptr)
	{
		UE_LOG(CriticalErrors, All, TEXT("AprototypeGameMode: BasicTileBPClass.Class is null!"));
	}

	DefaultPawnClass = PlayerPawnBPClass.Class;
	BasicTileBlueprintClass = BasicTileBPClass.Class;
}

void AprototypeGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	//Generate the map prior to the EnteringMap state

	FVector SpawnLocation = FVector(1060.0f, 20.0f, 318.0f);
	FRotator InitialRotation = FRotator(0.0f, 0.0f, 0.0f);
	UWorld * World = GetWorld();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	ATriggerBox * BasicTile = Cast<ATriggerBox>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));

	//Testing placement
	//BasicTile->GetActorBounds(false, Origin, BoxExtent);
	//FVector NextSpawnLocationNoCollidingComponents = FVector(SpawnLocation.X, SpawnLocation.Y + (BoxExtent.Y / 2), SpawnLocation.Z);
	//BasicTile->GetActorBounds(true, Origin, BoxExtent);
	//FVector NextSpawnLocationYesCollidingComponents = FVector(SpawnLocation.X, SpawnLocation.Y + (BoxExtent.Y * 2), SpawnLocation.Z); <------ this one appears to place two of the tile components exactly side-by-side

	FVector Origin;
	FVector BoxExtent;
	BasicTile->GetActorBounds(true, Origin, BoxExtent);

	for (int i = 0; i < 5; i++)
	{
		SpawnLocation.Y -= BoxExtent.Y * 2;
		BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));
	}
	SpawnLocation = FVector(1060.0f, 20.0f, 318.0f);
	for (int i = 0; i < 5; i++)
	{
		SpawnLocation.Y += BoxExtent.Y * 2;
		BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation, SpawnInfo));
	}
}