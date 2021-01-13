// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
// KC
#include "Config/Constants/Level.h"
#include "Enums/EFloorTile.h"
#include "LevelMapTile.generated.h"

class AMapUnit;


UCLASS(Transient, Within=LevelMap, meta=(DisplayName="LevelMap Tile", ToolTip="Contains the necessary data and methods required to construct one grid point of a LevelMap."))
class ULevelMapTile : public UObject
{
    GENERATED_BODY()
public:
    void Init(
        FIntPoint const point,
        TCHAR const floorChar = FloorTile::EMPTY_CHAR,
        bool const hasWallNorth = false,
        bool const hasWallEast  = false,
        bool const hasWallSouth = false,
        bool const hasWallWest  = false
    );
    
    void Init(
        int32 const x,
        int32 const y,
        TCHAR const floorChar = FloorTile::EMPTY_CHAR,
        bool const hasWallNorth = false,
        bool const hasWallEast  = false,
        bool const hasWallSouth = false,
        bool const hasWallWest  = false
    );

    explicit operator bool() const;
    explicit operator TCHAR() const;
    
    void SetHasWallNorth( bool const hasWallNorth );
    void SetHasWallEast( bool const hasWallEast );
    void SetHasWallSouth( bool const hasWallSouth );
    void SetHasWallWest( bool const hasWallWest );
    
    void SetHasFoodTrough( bool const hasFoodTrough );
    void SetHasLitterBox( bool const hasLitterBox );
    
    bool TrySpawn();
    
protected:
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|FloorTile", meta=(DisplayName="Floor Character", ToolTip="The character representing the FloorTile actor at this grid point."))
    TCHAR FloorChar = FloorTile::EMPTY_CHAR;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Walls", meta=(DisplayName="Has Wall to the North", ToolTip="True if there is a wall to the north (x, y - 1) of this point."))
    bool bHasWallNorth = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Walls", meta=(DisplayName="Has Wall to the East", ToolTip="True if there is a wall to the east (x + 1, y) of this point."))
    bool bHasWallEast  = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Walls", meta=(DisplayName="Has Wall to the South", ToolTip="True if there is a wall to the south (x, y + 1) of this point."))
    bool bHasWallSouth = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Walls", meta=(DisplayName="Has Wall to the West", ToolTip="True if there is a wall to the west (x - 1, y) of this point."))
    bool bHasWallWest  = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Interactables", meta=(DisplayName="Has Food Trough", ToolTip="True if this point contains the food trough."))
    bool bHasFoodTrough = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map|Interactables", meta=(DisplayName="Has Litter Box", ToolTip="True if this point contains the litter box."))
    bool bHasLitterBox  = false;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map", meta=(DisplayName="Coordinates in LevelMap", ToolTip="The (x,y) location of this object within the containing LevelMap."))
    FIntPoint Coordinates = FIntPoint::NoneValue;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Map", meta=(DisplayName="Actor Instance", ToolTip="The actor instance which represents this LevelMap Tile in the world, if relevant (i.e. this map tile is not empty)."))
    AMapUnit* ActorInstance = nullptr;
};


// INLINE DEFINITIONS
/////////////////////
inline void ULevelMapTile::Init(
    int32 const x,
    int32 const y,
    TCHAR const floorChar,
    bool const hasWallNorth,
    bool const hasWallEast,
    bool const hasWallSouth,
    bool const hasWallWest
) {
    Init(
        FIntPoint{ x, y },
        floorChar,
        hasWallNorth, hasWallEast, hasWallSouth, hasWallWest
    );
}

inline ULevelMapTile::operator  bool() const
{ return !FloorTile::IsAbstract( FloorChar ); }

inline ULevelMapTile::operator TCHAR() const
{ return FloorChar; }

inline void ULevelMapTile::SetHasWallNorth( bool const hasWallNorth )
{ bHasWallNorth = hasWallNorth; }

inline void ULevelMapTile::SetHasWallEast( bool const hasWallEast )
{ bHasWallEast = hasWallEast; }

inline void ULevelMapTile::SetHasWallSouth( bool const hasWallSouth )
{ bHasWallSouth = hasWallSouth; }

inline void ULevelMapTile::SetHasWallWest( bool const hasWallWest )
{ bHasWallWest = hasWallWest; }

inline void ULevelMapTile::SetHasFoodTrough( bool const hasFoodTrough )
{ bHasFoodTrough = hasFoodTrough; }

inline void ULevelMapTile::SetHasLitterBox ( bool const hasLitterBox )
{ bHasLitterBox = hasLitterBox; }
