// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SandpointGameMode.h"
#include "SandpointHUD.h"
#include "SandpointCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASandpointGameMode::ASandpointGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASandpointHUD::StaticClass();
}
