// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "LevelBuildTrigger_Bounds.generated.h"

USTRUCT()
struct FBuildTrigger_Bounds
{
	GENERATED_USTRUCT_BODY()

	uint32 LevelPosition_X;
	uint32 LevelPosition_Y;

};

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ULevelBuildTrigger_Bounds : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	ULevelBuildTrigger_Bounds(const FObjectInitializer&);
	void InitLevelBuildTrigger(FVector BoxExtent);

private:
	TSubclassOf<ATriggerBox> BasicTileBlueprintClass;
	ATriggerBox * Spawn_BasicTileBlueprint(const FVector &SpawnLocation, const FRotator &InitialRotation);
};