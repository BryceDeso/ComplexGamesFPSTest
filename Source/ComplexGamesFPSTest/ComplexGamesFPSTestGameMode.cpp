// Copyright Epic Games, Inc. All Rights Reserved.

#include "ComplexGamesFPSTestGameMode.h"
#include "ComplexGamesFPSTestHUD.h"
#include "ComplexGamesFPSTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AComplexGamesFPSTestGameMode::AComplexGamesFPSTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AComplexGamesFPSTestHUD::StaticClass();
}
