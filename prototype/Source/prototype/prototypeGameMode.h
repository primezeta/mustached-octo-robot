// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "prototypeCharacter.h"
#include "Engine/TriggerBox.h"
#include "prototypeGameMode.generated.h"

UCLASS(minimalapi)
class AprototypeGameMode : public AGameMode
{
	GENERATED_BODY()

private:

	//The purpose of the "level builders" is to trigger a new section of the gameplay area to be generated
	UPROPERTY()
	TArray<AActor*> GameLevelBuilders;

public:
	AprototypeGameMode(const FObjectInitializer& ObjectInitializer);
	~AprototypeGameMode();
	static TSubclassOf<ATriggerBox> LevelExtenderSceneClass;
	//virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay();
	AActor * SpawnLevelBuildActorClass(const FVector &SpawnLocation, const FRotator &InitialRotation);
};



