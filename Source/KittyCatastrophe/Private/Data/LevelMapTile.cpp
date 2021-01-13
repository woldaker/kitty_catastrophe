// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Data/LevelMapTile.h"
// Engine
#include "Engine/DataTable.h"
// KC
#include "Actors/Level/MapUnit.h"
#include "Actors/Level/MapTile.h"
#include "Utils/Log.h"


void ULevelMapTile::Init(
    FIntPoint const point,
    TCHAR const floorChar,
    bool const hasWallNorth,
    bool const hasWallEast,
    bool const hasWallSouth,
    bool const hasWallWest
) {
    checkf(
        KC::LEVEL::MAP::IsValidPoint( point ),
        TEXT("Invalid map unit (%d,%d) with which to initialize a LevelMapTile."),
        point.X, point.Y
    );
    
    Coordinates = point;
    checkf(
        FloorTile::IsValid( floorChar ),
        TEXT("Invalid FloorTile character '%s'."), floorChar
    );
    
    if (FloorTile::IsEmpty( floorChar ))
    {
        checkf(
            !(hasWallNorth || hasWallEast || hasWallSouth || hasWallWest),
            TEXT("Only non-empty FloorTiles can be surrounded by WallTiles.")
        );
    }
    
    FloorChar = floorChar;
    bHasWallNorth = hasWallNorth;
    bHasWallEast  = hasWallEast;
    bHasWallSouth = hasWallSouth;
    bHasWallWest  = hasWallWest;
}


bool ULevelMapTile::TrySpawn()
{
    namespace MAPTILE = KC::LEVEL::MAP::TILE;
    using ESpawnActorNameMode = FActorSpawnParameters::ESpawnActorNameMode;
    
    if (ActorInstance)
    {
        Log::Warn(
            "LevelMap Tile at ({0},{1}) has already spawned its actors.",
            Coordinates.X, Coordinates.Y
        );
        return true;
    }
 
    if (FloorTile::IsAbstract( FloorChar ))
    {
        Log::Info(
            "Skipping spawn of level actors for LevelMap Tile at ({0},{1}): this map unit is empty.",
            Coordinates.X, Coordinates.Y
        );
        return false;
    }
    
    UWorld* world = GetWorld();
    checkf( world, TEXT("Cannot get UWorld instance.") );
    
    FString const mapPointID = FString::Printf(
        TEXT("MapPoint_%02d_%02d"),
        Coordinates.X,
        Coordinates.Y
    );
#if WITH_EDITOR
    FString const mapPointName = FString::Printf(
        TEXT("MapPoint (%d,%d)"),
        Coordinates.X,
        Coordinates.Y
    );
#endif
    FVector const spawnLoc =
    {
        Coordinates.X * AMapTile::GetUnitLength(),
        Coordinates.Y * AMapTile::GetUnitLength(),
        0.0f
    };
    
    FRotator const spawnRot = FRotator::ZeroRotator;
    
    FActorSpawnParameters spawnParams;
    spawnParams.Name     = *mapPointID;
    spawnParams.NameMode = ESpawnActorNameMode::Required_ErrorAndReturnNull;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    ActorInstance = world->SpawnActor<AMapUnit>(
        spawnLoc,
        spawnRot,
        spawnParams
    );
    
    checkf(
        ActorInstance,
        TEXT("Actor instance for LevelMapTile (%d,%d) could not be spawned."),
        Coordinates.X, Coordinates.Y
    );
#if WITH_EDITOR
    ActorInstance->SetActorLabel( mapPointName, false );
#endif
    ActorInstance->Init(
        Coordinates,
        FloorChar,
        bHasWallNorth,
        bHasWallEast,
        bHasWallSouth,
        bHasWallWest
    );
    
    return true;
}
