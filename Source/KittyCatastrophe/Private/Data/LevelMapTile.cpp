// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Data/LevelMapTile.h"
// Engine
#include "Engine/DataTable.h"
// KC
#include "Actors/Level/MapPoint.h"
#include "Actors/Level/MapTile.h"
//#include "Config/Constants/Log.h"
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
        TEXT(/*KCINFO*/ "Invalid map point (%d,%d) with which to initialize a LevelMapTile."),
        point.X, point.Y
    );
    
    Coordinates = point;
    checkf(
        FloorTile::IsValid( floorChar ),
        TEXT(/*KCINFO*/ "Invalid FloorTile character '%s'."), floorChar
    );
    
    if (FloorTile::IsEmpty( floorChar ))
    {
        checkf(
            !(hasWallNorth || hasWallEast || hasWallSouth || hasWallWest),
            TEXT(/*KCINFO*/ "Only non-empty FloorTiles can be surrounded by WallTiles.")
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
            "Skipping spawn of level actors for LevelMap Tile at ({0},{1}): this map point is empty.",
            Coordinates.X, Coordinates.Y
        );
        return false;
    }
    
    UWorld* world = GetWorld();
    checkf( world, TEXT(/*KCINFO*/ "Cannot get UWorld instance.") );
    
    FVector const spawnLoc =
    {
        Coordinates.X * 2 * AMapTile::GetUnitExtent(),
        Coordinates.Y * 2 * AMapTile::GetUnitExtent(),
        0.0f
    };
    
    FRotator const spawnRot = FRotator::ZeroRotator;
    
    FActorSpawnParameters spawnParams;
    
    spawnParams.Name = *FString::Printf(
        TEXT("MapPoint_%d_%d"),
        Coordinates.X, Coordinates.Y
    );
    spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
    spawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    ActorInstance = world->SpawnActor<AMapPoint>(
        spawnLoc,
        spawnRot,
        spawnParams
    );
    
    checkf(
        ActorInstance,
        TEXT(/*KCINFO*/ "Actor instance for LevelMapTile (%d,%d) could not be spawned."),
        Coordinates.X, Coordinates.Y
    );
    
    ActorInstance->Init(
        FloorChar,
        bHasWallNorth, bHasWallEast, bHasWallSouth, bHasWallWest
    );
    
    return true;
}
