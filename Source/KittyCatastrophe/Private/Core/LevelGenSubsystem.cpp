// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Core/LevelGenSubsystem.h"
// Engine
//#include "Engine/DataTable.h"
// KC
#include "Actors/Level/FloorTile.h"
#include "Config/Constants/Level.h"
#include "Core/KCGameState.h"
#include "Data/LevelMap.h"
#include "Utils/Log.h"


ULevelGenSubsystem::ULevelGenSubsystem()
{
    LevelMap = CreateDefaultSubobject<ULevelMap>( TEXT("Level Map") );
    checkf( LevelMap, TEXT("Couldn't construct Level Map.") );
}

/*
void ULevelGenSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
}


void ULevelGenSubsystem::Deinitialize()
{
}
*/


bool ULevelGenSubsystem::TryLoadLevel( int32 const levelNumber )
{
    namespace MAPFILE = KC::LEVEL::MAP::FILE;
    
    if (!LevelMap->TryLoadLevelMapFromFile( MAPFILE::ConstructPath( levelNumber ) ))
    {
        Log::Error( "Error loading LevelMap for level {0}.", levelNumber );
        return false;
    }

    Log::Info( "LevelMap:\n{0}", LevelMap->ToString() );
    
    return LevelMap->TrySpawn();
}


bool ULevelGenSubsystem::TryLoadNextLevel()
{
    UWorld* world = GetWorld();
    checkf( world, TEXT("Couldn't get world instance.") );

    AKCGameState* gameState = Cast<AKCGameState>( world->GetGameState() );
    checkf( gameState, TEXT("Couldn't get GameState instance.") );

    int32 const nextLevelNumber = gameState->GetNextLevelNumber();

    if (!TryLoadLevel( nextLevelNumber )) { return false; }
    
    gameState->SetCurrentLevelNumber( nextLevelNumber );
    
    OnLevelLoaded.Broadcast();
    return true;
}
