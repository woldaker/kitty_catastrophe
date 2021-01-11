// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/MapPoint.h"
// Engine
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
// KC
#include "Actors/Level/CeilingTile.h"
#include "Actors/Level/FloorTile.h"
#include "Actors/Level/WallTile.h"
#include "Config/Constants/Level.h"
//#include "Config/Constants/Log.h"
#include "Config/Constants/Path.h"
#include "Data/LUTEntry_BPClass_FloorTile.h"
#include "Data/LUTEntry_BPClass_WallTile.h"
#include "Enums/EFloorTile.h"
#include "Utils/Log.h"

/*
EAttachmentRule const AMapPoint::MapTileAttachRuleLoc   = EAttachmentRule::KeepRelative;
EAttachmentRule const AMapPoint::MapTileAttachRuleRot   = EAttachmentRule::KeepRelative;
EAttachmentRule const AMapPoint::MapTileAttachRuleScale = EAttachmentRule::KeepRelative;

bool const AMapPoint::MapTileAttachRuleWeld = false;

FAttachmentTransformRules const AMapPoint::MapTileAttachRules =
{
    AMapPoint::MapTileAttachRuleLoc,
    AMapPoint::MapTileAttachRuleRot,
    AMapPoint::MapTileAttachRuleScale,
    AMapPoint::MapTileAttachRuleWeld
};
*/

AMapPoint::AMapPoint()
{
    namespace DT = KC::PATH::ASSET::DATATABLE;
    using DTFinder = ConstructorHelpers::FObjectFinder<UDataTable>;
    
    static FString const PATH_DT_FLOORTILE = DT::ConstructPath( DT::TYPE::FLOORTILE );
    static DTFinder floorTileClasses ( *PATH_DT_FLOORTILE );
  
    Log::Info( "Path to DT FloorTile asset constructed as '{0}'", PATH_DT_FLOORTILE );
    
    //TODO: change to checkf
    if (floorTileClasses.Succeeded())
    {
        FloorTileLUT = floorTileClasses.Object;
    }
    
    static FString const PATH_DT_WALLTILE = DT::ConstructPath( DT::TYPE::WALLTILE );
    static DTFinder wallTileClasses ( *PATH_DT_WALLTILE );
  
    Log::Info( "Path to DT WallTile asset constructed as '{0}'", PATH_DT_WALLTILE );
    
    //TODO: change to checkf
    if (wallTileClasses.Succeeded())
    {
        WallTileLUT = wallTileClasses.Object;
    }

    PrimaryActorTick.bCanEverTick = true;
    SetCanBeDamaged( false );
    
    //bIgnoresOriginShifting = true;
    //bLockLocation = true;
    bRelevantForLevelBounds = true;
    
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT("Root") );
    checkf( RootComponent, TEXT(/*KCINFO*/ "Cannot create Root SceneComponent for MapPoint.") );
}


void AMapPoint::Init(
        TCHAR const floorTileChar,
        bool const hasNorthWall,
        bool const hasEastWall,
        bool const hasSouthWall,
        bool const hasWestWall
) {
    namespace ATTACH_RULES = KC::LEVEL::MAP::TILE::ATTACH_RULES;
    namespace WALL         = KC::LEVEL::MAP::TILE::WALL;
    
    //TODO: should return true if on map but empty?
    //TODO: if so, then this function should return void or maybe AMapPoint (pointer) and be renamed to Spawn()?
    if (FloorTile::IsAbstract( floorTileChar ))
    {
        Log::Info(
            "Skipping spawn of level actors for LevelMap Tile at ({0},{1}): this map point is empty."
        );
        return;
    }
    
    checkf( FloorTileLUT, TEXT(/*KCINFO*/ "No FloorTile BPClass LUT set.") );
    checkf(  WallTileLUT, TEXT(/*KCINFO*/ "No WallTile BPClass LUT set.") );
    
    // Lookup FloorTile class
    TCHAR const* floorTileName = FloorTile::GetName( floorTileChar );
    static FString const FLOORTILE_DT_CONTEXT = TEXT("FloorTile Lookup");
    
    FLUTEntry_BPClass_FloorTile* floorTileData =
        FloorTileLUT->FindRow<FLUTEntry_BPClass_FloorTile>(
            floorTileName,
            FLOORTILE_DT_CONTEXT
        );
    
    checkf(
        floorTileData,
        TEXT(/*KCINFO*/ "Cannot find FloorTile class with name '%s'."),
        floorTileName
    );
    
    TSubclassOf<AFloorTile> floorTileClass = floorTileData->BPClass;
    checkf(
        floorTileClass,
        TEXT(/*KCINFO*/ "Cannot initialize a MapPoint with floorChar '%c': No floor class associated with that char in LUT."),
        floorTileChar
    );
    
    // Lookup WallTile class
    TCHAR const* wallTileName = TEXT("Default");
    static FString const WALLTILE_DT_CONTEXT = TEXT("WallTile Lookup");
    
    FLUTEntry_BPClass_WallTile* wallTileData =
        WallTileLUT->FindRow<FLUTEntry_BPClass_WallTile>(
            wallTileName,
            WALLTILE_DT_CONTEXT
        );
    
    checkf(
        wallTileData,
        TEXT(/*KCINFO*/ "Cannot find WallTile class with name '%s'."),
        wallTileName
    );
    
    TSubclassOf<AWallTile> wallTileClass = wallTileData->BPClass;
    checkf(
        wallTileClass,
        TEXT(/*KCINFO*/ "Cannot initialize a MapPoint with no WallTile class to use.")
    );
    
    UWorld* world = GetWorld();
    checkf( world, TEXT(/*KCINFO*/ "Cannot get UWorld instance.") );
    
    Floor = world->SpawnActor<AFloorTile>( floorTileClass );
    checkf( Floor, TEXT(/*KCINFO*/ "Could not spawn FloorTile actor.") );
    
    // EAttachmentRule enum values:
    // KeepRelative
    //     Keeps current relative transform as the relative transform to the new parent.
    // KeepWorld
    //     Automatically calculates the relative transform such that the attached component
    //     maintains the same world transform.
    // SnapToTarget
    //     Snaps transform to the attach point.
    //
    /*
    EAttachmentRule const attachRuleLoc   = EAttachmentRule::KeepRelative;
    EAttachmentRule const attachRuleRot   = EAttachmentRule::KeepRelative;
    EAttachmentRule const attachRuleScale = EAttachmentRule::KeepRelative;
    bool const weldOnAttach = false;
    
    FAttachmentTransformRules const attachRules
    {
        attachRuleLoc,
        attachRuleRot,
        attachRuleScale,
        weldOnAttach
    };
    */
    Floor->AttachToActor( this, ATTACH_RULES::ALL, TEXT("FloorTile") );
    
    Ceiling = world->SpawnActor<ACeilingTile>();
    checkf(Ceiling, TEXT("Ceiling is null."));
    
    Ceiling->AttachToActor( Floor, ATTACH_RULES::ALL, TEXT("CeilingTile") );
    Ceiling->Init(AMapTile::GetUnitExtent() * WALL::HEIGHT_SCALE);
    
    if (hasNorthWall) { ConstructWall( wallTileClass, ECardinal::NORTH, world ); }
    if (hasEastWall)  { ConstructWall( wallTileClass, ECardinal::EAST,  world ); }
    if (hasSouthWall) { ConstructWall( wallTileClass, ECardinal::SOUTH, world ); }
    if (hasWestWall)  { ConstructWall( wallTileClass, ECardinal::WEST,  world ); }
}


void AMapPoint::ConstructWall(
    TSubclassOf<AWallTile> wallTileClass,
    ECardinal const direction,
    UWorld* world
) {
    namespace ATTACH_RULES = KC::LEVEL::MAP::TILE::ATTACH_RULES;
    
    FString const directionName = Cardinal::GetName( direction );
    AWallTile*& wall = GetWall( direction );
    
    if (wall)
    {
        Log::Warn( "{0} wall has already been constructed.", directionName );
        return;
    }
    
    if (!world) { world = GetWorld(); }
    checkf( world, TEXT(/*KCINFO*/ "UWorld pointer is null.") );
    
    wall = world->SpawnActor<AWallTile>( wallTileClass );
    checkf( wall, TEXT(/*KCINFO*/ "Could not spawn %s wall tile."), *directionName );
    
    wall->AttachToActor( Floor, ATTACH_RULES::ALL, FName{ *directionName } );
    wall->Orient( direction );
}
