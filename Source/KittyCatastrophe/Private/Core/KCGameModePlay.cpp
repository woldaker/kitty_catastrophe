// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Core/KCGameModePlay.h"
// KC
#include "Core/KCGameState.h"
#include "Core/KCHUD_InGame.h"
#include "Core/KCPlayerController.h"
#include "Core/KCPlayerState.h"
#include "Core/LevelGenSubsystem.h"


AKCGameModePlay::AKCGameModePlay()
{
    GameStateClass        = AKCGameState::StaticClass();
    PlayerStateClass      = AKCPlayerState::StaticClass();
    PlayerControllerClass = AKCPlayerController::StaticClass();
    HUDClass              = AKCHUD_InGame::StaticClass();
}

/*
void AKCGameModePlay::InitGame(FString const& mapName, FString const& options, FString& errorMessage)
{
    Super::InitGame(mapName, options, errorMessage);


}
*/


void AKCGameModePlay::InitGameState()
{
    Super::InitGameState();

    UWorld* world = GetWorld();
    checkf(world, TEXT("World instance is null."));
    
    ULevelGenSubsystem* levelGenerator = world->GetSubsystem<ULevelGenSubsystem>();
    checkf(levelGenerator, TEXT("Level Generator is null."));
    
    bLevelGenerated = levelGenerator->TryLoadNextLevel();
}


bool AKCGameModePlay::ReadyToStartMatch()
{
    return Super::ReadyToStartMatch() && bLevelGenerated;
}
