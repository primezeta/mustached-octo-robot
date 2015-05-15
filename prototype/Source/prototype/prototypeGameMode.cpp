// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "prototype.h"
#include "prototypeGameMode.h"

TSubclassOf<ATriggerBox> AprototypeGameMode::LevelExtenderSceneClass;

AprototypeGameMode::AprototypeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ATriggerBox> LevelExtenderSceneBP(TEXT("Blueprint'/Game/SideScroller/Blueprints/Trigger_ExtendLevel'"));
	if (LevelExtenderSceneBP.Class == nullptr)
	{
		UE_LOG(CriticalErrors, All, TEXT("AprototypeGameMode: LevelExtenderSceneBP.Class is null!"));
	}
	LevelExtenderSceneClass = LevelExtenderSceneBP.Class;
}

AprototypeGameMode::~AprototypeGameMode()
{
}

void AprototypeGameMode::StartPlay()
{
	AprototypeCharacter * Player = Cast<AprototypeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector InitialBuildTriggerLocation = Player->GetActorLocation();
	AActor * const Blocks = SpawnLevelBuildActorClass(InitialBuildTriggerLocation, FRotator::ZeroRotator);
	GameLevelBuilders.Append(&Blocks, 1);
}

AActor * AprototypeGameMode::SpawnLevelBuildActorClass(const FVector &SpawnLocation, const FRotator &InitialRotation)
{
	return GetWorld()->SpawnActor(LevelExtenderSceneClass, &SpawnLocation, &InitialRotation);
}