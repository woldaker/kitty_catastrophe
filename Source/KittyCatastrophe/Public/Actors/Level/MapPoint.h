// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// KC
#include "Enums/ECardinal.h"
#include "MapPoint.generated.h"

class ACeilingTile;
class AFloorTile;
class AWallTile;
class UDataTable;


UCLASS(Category="Map", ClassGroup=(Map), meta=(DisplayName="Map Point", ToolTip="Actor which contains all other components necessary in order to completely spawn one (X,Y) point on a LevelMap."))
class KITTYCATASTROPHE_API AMapPoint : public AActor
{
    GENERATED_BODY()
public:
    AMapPoint();
    
    void Init(
        TCHAR const floorTileChar,
        bool const hasNorthWall,
        bool const hasEastWall,
        bool const hasSouthWall,
        bool const hasWestWall
    );
    
    bool HasWall( ECardinal const direction ) const;
    AWallTile*& GetWall( ECardinal const direction );
    
protected:
    // Attached actors
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Floor", ToolTip="The floor actor."))
    AFloorTile* Floor = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="North Wall", ToolTip="The north wall actor."))
    AWallTile* NorthWall = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="East Wall", ToolTip="The east wall actor."))
    AWallTile* EastWall = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="South Wall", ToolTip="The south wall actor."))
    AWallTile* SouthWall = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="West Wall", ToolTip="The west wall actor."))
    AWallTile* WestWall = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Ceiling", ToolTip="An invisible CeilingTile actor."))
    ACeilingTile* Ceiling = nullptr;

    // BP Class lookup tables
    UPROPERTY(meta=(DisplayName="FloorTile Class Lookup Table", ToolTip="Contains rows of type 'LUTEntry_BPClass_FloorTile'."))
    UDataTable* FloorTileLUT = nullptr;
    
    UPROPERTY(meta=(DisplayName="WallTile Class Lookup Table", ToolTip="Contains rows of type 'LUTEntry_BPClass_WallTile'."))
    UDataTable* WallTileLUT = nullptr;
    
    
    void ConstructWall(
        TSubclassOf<AWallTile> wallTileClass,
        ECardinal const direction,
        UWorld* world = nullptr
    );
/*
    static EAttachmentRule const MapTileAttachRuleLoc;
    static EAttachmentRule const MapTileAttachRuleRot;
    static EAttachmentRule const MapTileAttachRuleScale;
    
    static bool const            MapTileAttachRuleWeld;
    
    static FAttachmentTransformRules const MapTileAttachRules;
*/
};


// INLINE DEFINITIONS
/////////////////////
inline bool AMapPoint::HasWall( ECardinal const direction ) const
{
    switch(direction)
    {
    case ECardinal::NORTH:
        return NorthWall;
    case ECardinal::EAST:
        return EastWall;
    case ECardinal::SOUTH:
        return SouthWall;
    case ECardinal::WEST:
        return WestWall;
    default:
        checkNoEntry();
        return false;
    }
}

inline AWallTile*& AMapPoint::GetWall( ECardinal const direction )
{
    switch(direction)
    {
    case ECardinal::NORTH:
        return NorthWall;
    case ECardinal::EAST:
        return EastWall;
    case ECardinal::SOUTH:
        return SouthWall;
    case ECardinal::WEST:
        return WestWall;
    default:
        checkNoEntry();
        return NorthWall;
    }
}
