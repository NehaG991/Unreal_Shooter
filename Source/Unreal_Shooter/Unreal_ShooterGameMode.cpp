// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_ShooterGameMode.h"
#include "Unreal_ShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_ShooterGameMode::AUnreal_ShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

//   /Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter