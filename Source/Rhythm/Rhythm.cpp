// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rhythm.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Rhythm, "Rhythm" );

DEFINE_LOG_CATEGORY(LogRhythm)

void LoudError(FString const& errorMessage, uint64 id)
{
	UE_LOG(LogRhythm, Error, TEXT("%s"), *errorMessage);
	GEngine->AddOnScreenDebugMessage(id, 4, FColor::Red, errorMessage);
}
