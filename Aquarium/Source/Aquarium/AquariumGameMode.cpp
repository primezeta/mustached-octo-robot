// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Aquarium.h"
#include "AquariumGameMode.h"
#include "AquariumPawn.h"

AAquariumGameMode::AAquariumGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AAquariumPawn::StaticClass();
}
