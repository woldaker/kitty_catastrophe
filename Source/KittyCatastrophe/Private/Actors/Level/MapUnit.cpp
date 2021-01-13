// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/MapUnit.h"
// Engine
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
// KC
#include "Actors/Level/CeilingTile.h"
#include "Actors/Level/FloorTile.h"
#include "Actors/Level/WallTile.h"
#include "Config/Constants/Level.h"
#include "Config/Constants/Path.h"
#include "Data/LUTEntry_BPClass_FloorTile.h"
#include "Data/LUTEntry_BPClass_WallTile.h"
#include "Enums/EFloorTile.h"
#include "Utils/Log.h"


AMapUnit::AMapUnit()
{
    namespace DT = KC::PATH::ASSET::DATATABLE;
    using DTFinder = ConstructorHelpers::FObjectFinder<UDataTable>;
    
    static FString const PATH_DT_FLOORTILE = DT::ConstructPath( DT::TYPE::FLOORTILE );
    static DTFinder dtFloorTiles ( *PATH_DT_FLOORTILE );
    
    checkf(dtFloorTiles.Succeeded(), TEXT("DataTable for (BPClass: FloorTile) cannot be fetched."));
    FloorTileLUT = dtFloorTiles.Object;
    
    static FString const PATH_DT_WALLTILE = DT::ConstructPath( DT::TYPE::WALLTILE );
    static DTFinder dtWallTiles ( *PATH_DT_WALLTILE );
    
    checkf(dtWallTiles.Succeeded(), TEXT("DataTable for (BPClass: WallTile) cannot be fetched."));
    WallTileLUT = dtWallTiles.Object;
    
    PrimaryActorTick.bCanEverTick = true;
    SetCanBeDamaged( false );
    
    //bIgnoresOriginShifting = true;
    //bLockLocation = true;
    bRelevantForLevelBounds = true;
    
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT("Root") );
    checkf( RootComponent, TEXT("Cannot create Root SceneComponent for MapPoint.") );
}


void AMapPoint::Init(
    FIntPoint const& location,
    TCHAR const floorTileChar,
    bool const hasNorthWall,
    bool const hasEastWall,
    bool const hasSouthWall,
    bool const hasWestWall
) {
    namespace ATTACH_RULES = KC::LEVEL::MAP::TILE::ATTACH_RULES;
    namespace WALL         = KC::LEVEL::MAP::TILE::WALL;
    using ESpawnActorNameMode = FActorSpawnParameters::ESpawnActorNameMode;
    
    //TODO: should return true if on map but empty?
    //TODO: if so, then this function should return void or maybe AMapUnit (pointer) and be renamed to Spawn()?
    if (FloorTile::IsAbstract( floorTileChar ))
    {
        Log::Info(
            "Skipping spawn of level actors for LevelMap Tile at ({0},{1}): this map unit is empty."
        );
        return;
    }
    
    checkf( FloorTileLUT, TEXT("No FloorTile BPClass LUT set.") );
    checkf(  WallTileLUT, TEXT("No WallTile BPClass LUT set.") );
    
    // Lookup FloorTile class
    TCHAR const* floorTileClassName = FloorTile::GetName( floorTileChar );
    static FString const FLOORTILE_DT_CONTEXT = TEXT("FloorTile Lookup");
    
    FLUTEntry_BPClass_FloorTile* floorTileData =
        FloorTileLUT->FindRow<FLUTEntry_BPClass_FloorTile>(
            floorTileClassName,
            FLOORTILE_DT_CONTEXT
        );
    
    checkf(
        floorTileData,
        TEXT("Cannot find FloorTile class with name '%s'."),
        floorTileClassName
    );
    
    TSubclassOf<AFloorTile> floorTileClass = floorTileData->BPClass;
    checkf(
        floorTileClass,
        TEXT("Cannot initialize a MapPoint with floorChar '%c': No floor class associated with that char in LUT."),
        floorTileChar
    );
    
    // Lookup WallTile class
    TCHAR const* wallTileClassName = TEXT("Default");
    static FString const WALLTILE_DT_CONTEXT = TEXT("WallTile Lookup");
    
    FLUTEntry_BPClass_WallTile* wallTileData =
        WallTileLUT->FindRow<FLUTEntry_BPClass_WallTile>(
            wallTileClassName,
            WALLTILE_DT_CONTEXT
        );
    
    checkf(
        wallTileData,
        TEXT("Cannot find WallTile class with name '%s'."),
        wallTileClassName
    );
    
    TSubclassOf<AWallTile> wallTileClass = wallTileData->BPClass;
    checkf(
        wallTileClass,
        TEXT("Cannot initialize a MapPoint with no WallTile class to use.")
    );
    
    UWorld* world = GetWorld();
    checkf( world, TEXT("Cannot get UWorld instance.") );
    
    FString const floorTileID = FString::Printf(
        TEXT("FloorTile_%02d_%02d"),
        location.X,
        location.Y
    );
#if WITH_EDITOR
    FString const floorTileName = FString::Printf(
        TEXT("FloorTile (%d,%d)"),
        location.X,
        location.Y
    );
#endif
    FActorSpawnParameters floorSpawnParams;
    floorSpawnParams.Name     = *floorTileID;
    floorSpawnParams.NameMode = ESpawnActorNameMode::Required_ErrorAndReturnNull;
    floorSpawnParams.Owner    = this;
    floorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    Floor = world->SpawnActor<AFloorTile>( floorTileClass, floorSpawnParams );
    checkf( Floor, TEXT("Could not spawn FloorTile actor.") );
#if WITH_EDITOR
    Floor->SetActorLabel( floorTileName, false );
#endif
    Floor->AttachToActor( this, ATTACH_RULES::ALL, TEXT("FloorTile") );
    
    FString const ceilingTileID = FString::Printf(
        TEXT("CeilingTile_%02d_%02d"),
        location.X,
        location.Y
    );
#if WITH_EDITOR
    FString const ceilingTileName = FString::Printf(
        TEXT("CeilingTile (%d,%d)"),
        location.X,
        location.Y
    );
#endif
    FActorSpawnParameters ceilingSpawnParams;
    ceilingSpawnParams.Name     = *ceilingTileID;
    ceilingSpawnParams.NameMode = ESpawnActorNameMode::Required_ErrorAndReturnNull;
    ceilingSpawnParams.Owner    = this;
    ceilingSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    Ceiling = world->SpawnActor<ACeilingTile>( ceilingSpawnParams );
    checkf(Ceiling, TEXT("Ceiling is null."));
#if WITH_EDITOR
    Ceiling->SetActorLabel( ceilingTileName, false );
#endif
    Ceiling->AttachToActor( Floor, ATTACH_RULES::ALL, TEXT("CeilingTile") );
    Ceiling->Init(AMapTile::GetUnitLength() * WALL::HEIGHT_SCALE);
    
    if (hasNorthWall) { ConstructWall( location, wallTileClass, ECardinal::NORTH, world ); }
    if (hasEastWall)  { ConstructWall( location, wallTileClass, ECardinal::EAST,  world ); }
    if (hasSouthWall) { ConstructWall( location, wallTileClass, ECardinal::SOUTH, world ); }
    if (hasWestWall)  { ConstructWall( location, wallTileClass, ECardinal::WEST,  world ); }
}


void AMapUnit::ConstructWall(
    FIntPoint const& location,
    TSubclassOf<AWallTile> wallTileClass,
    ECardinal const direction,
    UWorld* world
) {
    namespace ATTACH_RULES = KC::LEVEL::MAP::TILE::ATTACH_RULES;
    using ESpawnActorNameMode = FActorSpawnParameters::ESpawnActorNameMode;
    
    FString const directionName = Cardinal::GetName( direction );
    AWallTile*& wall = GetWall( direction );
    
    if (wall)
    {
        Log::Warn( "{0} wall has already been constructed.", directionName );
        return;
    }
    
    
    if (!world) { world = GetWorld(); }
    checkf( world, TEXT("UWorld pointer is null.") );
    
    FString const wallTileID = FString::Printf(
        TEXT("WallTile_%02d_%02d_%s"),
        location.X,
        location.Y,
        *directionName
    );
#if WITH_EDITOR
    FString const wallTileName = FString::Printf(
        TEXT("WallTile (%d,%d) %s"),
        location.X,
        location.Y,
        *directionName
    );
#endif
    FActorSpawnParameters spawnParams;
    spawnParams.Name     = *wallTileID;
    spawnParams.NameMode = ESpawnActorNameMode::Required_ErrorAndReturnNull;
    spawnParams.Owner    = this;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    wall = world->SpawnActor<AWallTile>( wallTileClass, spawnParams );
    checkf(wall, TEXT("Could not spawn %s WallTile."), *directionName);
#if WITH_EDITOR
    wall->SetActorLabel( wallTileName, false );
#endif
    wall->AttachToActor( Floor, ATTACH_RULES::ALL, FName{ *directionName } );
    wall->Orient( direction );
}


FTransform AMapUnit::GetFloorTransform( FIntPoint const& point )
{

}


FTransform AMapUnit::GetWallTransform( FIntPoint const& point, ECardinal const direction )
{

}


FTransform AMapUnit::GetCeilingTransform( FIntPoint const& point )
{

}
