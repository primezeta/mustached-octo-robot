// Fill out your copyright notice in the Description page of Project Settings.

#include "prototype.h"
#include "LevelBuildTrigger_Bounds.h"

static ConstructorHelpers::FClassFinder<ATriggerBox> BasicTileBP(TEXT("Blueprint'/Game/SideScroller/Blueprints/TriggerBox_BasicTile_Blueprint'"));
//static ConstructorHelpers::FObjectFinder<ATriggerBox> BasicTileBPClass(TEXT("Blueprint'/Game/SideScroller/Blueprints/TriggerBox_BasicTile_Blueprint.TriggerBox_BasicTile_Blueprint'"));

ULevelBuildTrigger_Bounds::ULevelBuildTrigger_Bounds(const FObjectInitializer& Initializer) : Super(Initializer)
{
	if (BasicTileBP.Class == nullptr)
	{
		UE_LOG(CriticalErrors, All, TEXT("AprototypeGameMode: BasicTileBPClass.Class is null!"));
	}
	BasicTileBlueprintClass = BasicTileBP.Class;
}

void ULevelBuildTrigger_Bounds::InitLevelBuildTrigger(FVector BoxExtent)
{
	SetBoxExtent(BoxExtent);
}

ATriggerBox * ULevelBuildTrigger_Bounds::Spawn_BasicTileBlueprint(const FVector &SpawnLocation, const FRotator &InitialRotation)
{
	UWorld * World = GetWorld();
	return static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation));

	//ATriggerBox * BasicTile = Cast<ATriggerBox>(World->SpawnActor(BasicTileBlueprintClass->GetClass(), SpawnLocation, InitialRotation));
	//FVector Origin;
	//FVector BoxExtent;
	//BasicTile->GetActorBounds(true, Origin, BoxExtent);
	//for (int i = 0; i < 5; i++)
	//{
	//	SpawnLocation.Y -= BoxExtent.Y * 2;
	//	BasicTile = static_cast<ATriggerBox*>(World->SpawnActor(BasicTileBlueprintClass, &SpawnLocation, &InitialRotation));
	//}
}