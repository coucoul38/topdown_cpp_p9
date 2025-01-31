// Copyright Epic Games, Inc. All Rights Reserved.

#include "topdown_cppGameMode.h"
#include "topdown_cppPlayerController.h"
#include "topdown_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"

Atopdown_cppGameMode::Atopdown_cppGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Atopdown_cppPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}