// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "LevelBuildTrigger_Bounds.h"
#include "prototypeGameMode.generated.h"

UCLASS(minimalapi)
class AprototypeGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	void LevelBuildTriggerResponse();
	FBuildTrigger_Bounds LevelBuildTriggers[];

public:
	AprototypeGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
};



