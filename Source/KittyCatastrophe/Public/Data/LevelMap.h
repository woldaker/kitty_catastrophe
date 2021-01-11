// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "HAL/Platform.h"
// KC
#include "Config/Constants/Level.h"
#include "Data/LevelMapTile.h"
#include "LevelMap.generated.h"

class UDataTable;


USTRUCT(meta=(DisplayName="IntPoint Pair", ToolTip="A pair of (X,Y) integer points."))
struct FIntPointPair
{
    GENERATED_BODY()
    
    FIntPointPair(
        FIntPoint const first  = FIntPoint::ZeroValue,
        FIntPoint const second = FIntPoint::ZeroValue
    );
    
    FIntPointPair(
        int32 const  firstX, int32 const  firstY,
        int32 const secondX, int32 const secondY
    );
    
    FIntPointPair(
        int32 const  firstXY,
        int32 const secondXY
    );
    
    
    bool IsValid() const;
    void Reset();
    
    bool IsZeroed() const;
    
    FString ToString() const;
    
    UPROPERTY(meta=(DisplayName="First", ToolTip="The first IntPoint in the pair."))
    FIntPoint First = FIntPoint::ZeroValue;
    
    UPROPERTY(meta=(DisplayName="Second", ToolTip="The second IntPoint in the pair."))
    FIntPoint Second = FIntPoint::ZeroValue;
};


USTRUCT(meta=(DisplayName="Bounding Box 2D", ToolTip="A bounding box for 2 dimensions: First (X,Y) (inclusive) to Second (X,Y) (exclusive)."))
struct FBoundingBox2D : public FIntPointPair
{
    GENERATED_BODY()
    FBoundingBox2D(
        FIntPoint const lower = FIntPoint::ZeroValue,
        FIntPoint const upper = FIntPoint::ZeroValue
    );
    
    bool IsValid() const;
};


USTRUCT(meta=(DisplayName="Wall Segment", ToolTip="Contains two integer points which are the start and end of the wall segment.  Must be either perfectly horizontal or perfectly vertical along either the X or Y axis."))
struct FWallSegment : public FIntPointPair
{
    GENERATED_BODY()
    
    FWallSegment(
        FIntPoint const start = FIntPoint::ZeroValue,
        FIntPoint const end   = FIntPoint::ZeroValue
    );
    
    bool IsHorizontal() const;
    bool IsVertical() const;
    
    bool IsValid( bool const InConstructor = false ) const;
    
    int32 GetLength() const;
    
    // Returns all map points on either side of the wall, but not extending off the ends.
    TArray<FIntPointPair> GetAdjacentMapPoints() const;
};


USTRUCT(meta=(DisplayName="LevelMap Tile Array"))
struct FLevelMapTileArray
{
    GENERATED_BODY()

    UPROPERTY(meta=(DisplayName="Tiles"))
    TArray<ULevelMapTile*> Tiles;
};


// ULevelMap
//////////////////////
UCLASS(Within=LevelGenSubsystem, Category="Map", meta=(DisplayName="Level Map", ToolTip="Decodes and then contains and operates on the data obtained from LevelMap files."))
class ULevelMap : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(meta=(DisplayName="Initialize", ToolTip="Sets the map's width and height and fills it with empty MapTiles."))
    void Init(
        UPARAM(DisplayName="Width")
        int32 const width,
        UPARAM(DisplayName="Height")
        int32 const height
    );

    //UFUNCTION(meta=(DisplayName="Get Bounding Box"))
    //FBoundingBox2D const& GetBoundingBox() const;
    
    //UFUNCTION(meta=(DisplayName="Get Width"))
    //int32 GetWidth() const;
    
    //UFUNCTION(meta=(DisplayName="Get Height"))
    //int32 GetHeight() const;
    
    //UFUNCTION(meta=(DisplayName="Contains Point", ToolTip="If EmptyOK is true, returns true when point is within Bounding Box.  If EmptyOK is false, returns true only when point is on the Map."))
    bool ContainsPoint(
        //UPARAM(DisplayName="Point")
        FIntPoint const point,
        //UPARAM(DisplayName="Empty OK")
        bool const emptyOK = false
    ) const;
    
    bool ContainsPoint( int32 const x, int32 const y, bool const emptyOK = false ) const;

    //UFUNCTION(meta=(DisplayName="Load LevelMap from File", ToolTip="Returns true on success."))
    bool TryLoadLevelMapFromFile( FString const& filepath );

    void EnsureValidPoint( FIntPoint const point );
    
    //UFUNCTION(meta=(DisplayName="Ensure Valid Point", ToolTip="If point at (X,Y) exists, do nothing, else adds default/blank elements until it does.  Cannot be called with negative index values."))
    void EnsureValidPoint(
        //UPARAM(meta=(DisplayName="X", ClampMin=0))
        int32 const x,
        //UPARAM(meta=(DisplayName="Y", ClampMin=0))
        int32 const y
    );
    
    UFUNCTION(meta=(DisplayName="Spawn", ToolTip="Attempts to spawn all level actors represented by the data in the Map.  Returns false on failure."))
    bool TrySpawn();
    
    UFUNCTION(meta=(DisplayName="To String", ToolTip="Returns a string representation of the currently loaded Map file."))
    FString const& ToString() const;

private:
    bool TryParseMapFileContents( TArray<FString> const& fileContents );
    
    TCHAR GetCharAt( FIntPoint const point ) const;
    TCHAR GetCharAt( int32 const x, int32 const y ) const;
    
    ULevelMapTile* GetMapTileAt( FIntPoint const point );
    ULevelMapTile* GetMapTileAt( int32 const x, int32 const y );
    
    bool TryAddWallSegment( FWallSegment const wall );
    bool TryAddWallSegment( FIntPoint const start, FIntPoint const end );
    
    template<typename T>
    void AppendToStringRepr( T const& messageChunk );
    
    template<typename T, typename... Args>
    void AppendToStringRepr( T const& messageChunk, Args&&... args );
    
    void InvalidateStringRepr();
    void   ValidateStringRepr();

// DATA MEMBERS
    // BoundingBox is initialized to First=[maximum values] and Second=[minimum values].
    // Post-initialize, both First and Second will have their values adjusted until they're deemed correct;
    //   First will only be adjusted by decreasing its value, and Second only by increasing it.
    UPROPERTY(meta=(DisplayName="Bounding Box"))
    FBoundingBox2D BoundingBox = {KC::LEVEL::MAP::POINT_MAX, KC::LEVEL::MAP::POINT_MIN};

    UPROPERTY(meta=(DisplayName="Food Trough Location"))
    FIntPoint FoodTroughLocation = FIntPoint::NoneValue;
    
    UPROPERTY(meta=(DisplayName="Litter Box Location"))
    FIntPoint LitterBoxLocation = FIntPoint::NoneValue;

    UPROPERTY(meta=(DisplayName="Map"))
    TArray<FLevelMapTileArray> Map;
    
    UPROPERTY(meta=(DisplayName="String Representation"))
    FString StringRepr = {};
    
    UPROPERTY(meta=(DisplayName="String Representation is Valid"))
    bool bStringReprIsValid = true;
};



// INLINE DEFINITIONS
/////////////////////
// FIntPointPair
inline FIntPointPair::FIntPointPair( FIntPoint const first, FIntPoint const second ) :
    First( first ),
    Second( second )
{}

inline FIntPointPair::FIntPointPair(
    int32 const  firstX, int32 const  firstY,
    int32 const secondX, int32 const secondY
) :
    FIntPointPair( FIntPoint{firstX, firstY}, FIntPoint{secondX, secondY} )
{}

inline FIntPointPair::FIntPointPair( int32 const firstXY, int32 const secondXY ) :
    FIntPointPair( FIntPoint{firstXY, firstXY}, FIntPoint{secondXY, secondXY} )
{}

inline bool FIntPointPair::IsValid() const
{
    return (First.X != INDEX_NONE) &&  (First.Y != INDEX_NONE) &&
          (Second.X != INDEX_NONE) && (Second.Y != INDEX_NONE);
}

inline void FIntPointPair::Reset()
{
    First  = FIntPoint::ZeroValue;
    Second = FIntPoint::ZeroValue;
}

inline bool FIntPointPair::IsZeroed() const
{
    return (First == FIntPoint::ZeroValue) && (Second == FIntPoint::ZeroValue);
}

inline FString FIntPointPair::ToString() const
{
    return FString::Printf( TEXT("(%d,%d) -> (%d,%d)"), First.X, First.Y, Second.X, Second.Y );
}


// FBoundingBox2D
/////////////////
inline FBoundingBox2D::FBoundingBox2D( FIntPoint const lower, FIntPoint const upper ) :
    FIntPointPair( lower, upper )
{}

inline bool FBoundingBox2D::IsValid() const
{
    namespace MAP = KC::LEVEL::MAP;
    
    return FMath::IsWithinInclusive( Second.X, MAP::POINT_MIN, (MAP::POINT_MAX + 1) ) &&
           FMath::IsWithinInclusive( Second.Y, MAP::POINT_MIN, (MAP::POINT_MAX + 1) ) &&
           FMath::IsWithin( First.X, MAP::POINT_MIN, Second.X ) &&
           FMath::IsWithin( First.Y, MAP::POINT_MIN, Second.Y );
}


// FWallSegment
///////////////
inline bool FWallSegment::IsHorizontal() const { return (First.Y == Second.Y); }
inline bool FWallSegment::IsVertical() const   { return (First.X == Second.X); }

inline bool FWallSegment::IsValid( bool const inConstructor ) const
{
    return FIntPointPair::IsValid() &&
    (
        (inConstructor && IsZeroed()) ||
        (IsHorizontal() ^ IsVertical())
    );
}

inline int32 FWallSegment::GetLength() const
{
    // Because FWallSegments fail during construction if they are not perfectly either
    //   horizontal or vertical, (Second - First) will either produce (0,Length) or (Length,0)
    return (Second - First).GetMax();
}


// ULevelMap
////////////
//inline FBoundingBox2D const& ULevelMap::GetBoundingBox() const { return BoundingBox; }
//inline int32 ULevelMap::GetWidth() const { return BoundingBox.Second.X - BoundingBox.First.X; }
//inline int32 ULevelMap::GetHeight() const { return BoundingBox.Second.Y - BoundingBox.First.Y; }

inline bool ULevelMap::ContainsPoint( int32 const x, int32 const y, bool const emptyOK ) const
{
    return ContainsPoint( FIntPoint{x,y}, emptyOK );
}


inline TCHAR ULevelMap::GetCharAt( int32 const x, int32 const y ) const
{
    return GetCharAt( FIntPoint{x,y} );
}


inline ULevelMapTile* ULevelMap::GetMapTileAt( int32 const x, int32 const y )
{
    return GetMapTileAt( FIntPoint{x,y} );
}

inline void ULevelMap::EnsureValidPoint( int32 const x, int32 const y )
{
    EnsureValidPoint( FIntPoint{x,y} );
}

inline bool ULevelMap::TryAddWallSegment( FIntPoint const start, FIntPoint const end )
{
    return TryAddWallSegment( FWallSegment{start,end} );
}

template<typename T>
inline void ULevelMap::AppendToStringRepr( T const& messageChunk )
{
    StringRepr += messageChunk;
}

template<typename T, typename... Args>
inline void ULevelMap::AppendToStringRepr( T const& messageChunk, Args&&... args )
{
    StringRepr += messageChunk;
    AppendToStringRepr( Forward<Args>(args)... );
}

inline void ULevelMap::InvalidateStringRepr() { bStringReprIsValid = false; }
inline void ULevelMap::ValidateStringRepr()   { bStringReprIsValid = true; }


inline FString const& ULevelMap::ToString() const {
    static FString const INVALID_STATE_MESSAGE = TEXT("LevelMap is in an invalid state!");
    
    return bStringReprIsValid ?
        StringRepr :
        INVALID_STATE_MESSAGE;
}
