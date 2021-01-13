// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Data/LevelMap.h"
// Engine
#include "Engine/DataTable.h"
// KC
#include "Actors/Level/FloorTile.h"
#include "Config/Constants/Path.h"
#include "Enums/EFloorTile.h"
#include "Utils/FileIO.h"
#include "Utils/Log.h"
#include "Utils/StringParser.h"


void ULevelMap::Init( int32 const width, int32 const height )
{
    namespace MAP = KC::LEVEL::MAP;
    
    checkf(MAP::IsValidLength( width ) && MAP::IsValidLength( height ),
           TEXT("Cannot initialize LevelMap to size (%d x %d):  width and height must both be in range [%d - %d]."),
           width,
           height,
           MAP::LENGTH_MIN,
           MAP::LENGTH_MAX
    );
    
    Map.SetNum( width );
    
    for (int32 col = 0; col < width; ++col)
    {
        Map[ col ].Tiles.SetNum( height );
        
        for (int32 row = 0; row < height; ++row)
        {
            Map[ col ].Tiles[ row ] = NewObject<ULevelMapTile>( this );
        }
    }
    
    BoundingBox = { FIntPoint::ZeroValue, { width, height } };
}


bool ULevelMap::TryLoadLevelMapFromFile( FString const& filepath )
{
    ValidateStringRepr();
    TArray<FString> fileContents;
    
    if (!UFileIO::TryLoadFileToStringArray( fileContents, filepath ))
    {
        Log::Error( "Could not read from Map file '{0}'", filepath );
        InvalidateStringRepr();
        return false;
    }
    
    if (!TryParseMapFileContents( fileContents ))
    {
        Log::Error( "Could not parse contents of Map file '{0}'", filepath );
        InvalidateStringRepr();
        return false;
    }
    
    return true;
}


bool ULevelMap::TryParseMapFileContents( TArray<FString> const& fileContents )
{
    namespace MAP = KC::LEVEL::MAP;
    namespace KEYVAL = MAP::FILE::KEYVAL;
    
    static FString const DT_CONTEXT = TEXT("FloorTile DT Context");
    
    checkf(
        (fileContents.Num() > 0),
        TEXT("LevelMap file contents cannot be empty.")
    );
    
    ValidateStringRepr();
    
    // Split the file contents into two parts:
    TArray<FString> mapSection;
    TArray<FString> keyvalSection;
    
    bool inMap = true;
    int32 mapWidth = 0;
    int32 mapHeight = 0;
    int32 emptyLineCount = 0;
    
    // Split file contents by the blank line
    for (FString const& line : fileContents)
    {
        if (line.IsEmpty())
        {
            ++emptyLineCount;
            inMap = false;
        }
        else
        {
            if (inMap)
            {
                mapSection.Add( line );
                mapWidth = FMath::Max( mapWidth, line.Len() );
                ++mapHeight;
            }
            else
            {
                keyvalSection.Add( line );
            }
            
            AppendToStringRepr( line );
        }
        
        AppendToStringRepr( TEXT("\n") );
    }
    
    if (emptyLineCount != 1)
    {
        Log::Error(
            "LevelMap file must contain exactly one empty line, which separates the map tiles from the additional "
            "map details below it."
        );
        return false;
    }
    
    Init( mapWidth, mapHeight );
    
    // Make sure all the strings in the map copy are of max length
    for (FString& line : mapSection)
    {
        int32 const padLength = (mapWidth - line.Len());
        if (padLength > 0)
        {
            line.Append( FString::ChrN( padLength, FloorTile::EMPTY_CHAR ) );
        }
    }
    
    // Loop through map section
    for (int32 y = 0; y < mapHeight; ++y)
    {
        FString const& line = mapSection[ y ];
        
        for (int32 x = 0; x < mapWidth; ++x)
        {
            TCHAR const& floorChar = line[ x ];
            
            if (FloorTile::IsEmpty( floorChar ))
            {
                Map[ x ].Tiles[ y ]->Init( x, y, floorChar );
                continue;
            }
            
            FloorTile::NeighborData const neighborData{ mapSection, x, y };
            
            Map[ x ].Tiles[ y ]->Init(
                x, y,
                floorChar,
                neighborData.IsVacant( ECardinal::NORTH ),
                neighborData.IsVacant( ECardinal::EAST ),
                neighborData.IsVacant( ECardinal::SOUTH ),
                neighborData.IsVacant( ECardinal::WEST )
            );
        }
    }
    
    bool hasLitterBox = false;
    bool hasFoodTrough = false;

    for (FString const& keyval : keyvalSection)
    {
        FString key;
        FString val;

        if (!StringParser::TryKeyVal( keyval, key, val ))
        {
            Log::Error( "Invalid key=val string: '{0}'.", keyval );
            InvalidateStringRepr();
            return false;
        }

        if (!KEYVAL::IsValidKey( key ))
        {
            Log::Error( "Invalid key string: '{0}'.", key );
            InvalidateStringRepr();
            return false;
        }
        
        if (key == KEYVAL::WALL)
        {
            TArray<FIntPoint> range;
            if (!StringParser::TryIntPointRange( val, range ))
            {
                Log::Error( "Invalid LevelMap value string for key '{0}': '{1}'.", key, val );
                InvalidateStringRepr();
                return false;
            }
            
            for (int32 current = 0, next = 1; next < range.Num(); ++current, ++next)
            {
                if (!TryAddWallSegment( range[ current ], range[ next ] ))
                {
                    return false;
                }
            }
        }
        else // not a wall section
        {
            FIntPoint point;
            
            if (!StringParser::TryIntPoint( val, point ))
            {
                Log::Error( "Invalid value string for key '{0}': '{1}'.", key, val );
                InvalidateStringRepr();
                return false;
            }
            
            if (!ContainsPoint( point ))
            {
                Log::Error( "Invalid point '({0},{1})':  not on map.", point.X, point.Y );
                InvalidateStringRepr();
                return false;
            }
            
            ULevelMapTile* maptile = GetMapTileAt( point );
            
            if (!maptile)
            {
                Log::Error( "Unable to fetch LevelMapTile object at point ({0},{1}).", point.X, point.Y );
                return false;
            }
            
            if (key == KEYVAL::LITTERBOX)
            {
                LitterBoxLocation = point;
                hasLitterBox = true;
                
                maptile->SetHasLitterBox( true );
            }
            else if (key == KEYVAL::FOODTROUGH)
            {
                FoodTroughLocation = point;
                hasFoodTrough = true;
                
                maptile->SetHasFoodTrough( true );
            }
            else {
                Log::Error( "Invalid key '{0}' in LevelMap file.", key );
                return false;
            }
        }
    }

    if (!(hasLitterBox && hasFoodTrough))
    {
        Log::Error(
            "Error parsing key=val pairs in Map file: Keys '{0}' and '{1}' must be present.",
            KEYVAL::LITTERBOX,
            KEYVAL::FOODTROUGH
        );
        
        InvalidateStringRepr();
        return false;
    }

    return true;
}


bool ULevelMap::TryAddWallSegment( FWallSegment const wall )
{
    TArray<FIntPointPair> adjacentPoints = wall.GetAdjacentMapPoints();
    
    // Make sure that all points on either side of the wall do actually exist
    for (FIntPointPair const& pointPair : adjacentPoints)
    {
        bool const containsFirstPoint  = ContainsPoint( pointPair.First );
        bool const containsSecondPoint = ContainsPoint( pointPair.Second );
        
        if (!(containsFirstPoint && containsSecondPoint))
        {
            FIntPoint const& missingPoint = containsFirstPoint ?
                pointPair.Second :
                pointPair.First;
            
            Log::Warn(
                "Invalid wall segment {0}: All points on both sides must exist on the map, "
                "but point ({1},{2}) does not exist.",
                wall.ToString(),
                missingPoint.X,
                missingPoint.Y
            );
            return false;
        }
    }
    
    for (FIntPointPair const& pointPair : adjacentPoints)
    {
        ULevelMapTile* tileFirst  = GetMapTileAt( pointPair.First );
        ULevelMapTile* tileSecond = GetMapTileAt( pointPair.Second );
     
        // TODO: remove for production
        checkf(
            tileFirst,
            TEXT("MapTile at ({0},{1}) doesn't exist"),
            pointPair.First.X,
            pointPair.First.Y
        );
        
        checkf(
            tileSecond,
            TEXT("MapTile at ({0},{1}) doesn't exist"),
            pointPair.Second.X,
            pointPair.Second.Y
        );
     
        if (wall.IsHorizontal())
        {
            tileFirst->SetHasWallSouth( true );
            tileSecond->SetHasWallNorth( true );
        }
        else
        {
            tileFirst->SetHasWallEast( true );
            tileSecond->SetHasWallWest( true );
        }
    }
        
    return true;
}


bool ULevelMap::ContainsPoint( FIntPoint const point, bool const emptyOK ) const
{
    if (!FMath::IsWithin( point.X, BoundingBox.First.X, BoundingBox.Second.X ) ||
        !FMath::IsWithin( point.Y, BoundingBox.First.Y, BoundingBox.Second.Y )
    ) {
        return false;
    }
    
    if (emptyOK) { return true; }
    
    ULevelMapTile* maptile = Map[ point.X ].Tiles[ point.Y ];
    
    return maptile && static_cast<bool>( *maptile );
}


TCHAR ULevelMap::GetCharAt( FIntPoint const point ) const
{
    return ContainsPoint( point ) ?
        static_cast<TCHAR>( *Map[ point.X ].Tiles[ point.Y ] ) :
        FloorTile::EMPTY_CHAR;
}


ULevelMapTile* ULevelMap::GetMapTileAt( FIntPoint const point )
{
    checkf(
        ContainsPoint( point, true ),
        TEXT("Map Unit (%d,%d) out of range."),
        point.X, point.Y
    );
    
    return Map[point.X].Tiles[point.Y];
}


void ULevelMap::EnsureValidPoint( FIntPoint const point )
{
    if (!Map.IsValidIndex( point.X ))
    {
        Map.SetNum( point.X + 1 );
    }
    
    if (!Map[ point.X ].Tiles.IsValidIndex( point.Y ))
    {
        Map[ point.X ].Tiles.SetNum( point.Y + 1 );
    }
}


bool ULevelMap::TrySpawn()
{
    for (int32 y = BoundingBox.First.Y; y < BoundingBox.Second.Y; ++y)
    {
        for (int32 x = BoundingBox.First.X; x < BoundingBox.Second.X; ++x)
        {
            if (!ContainsPoint( x, y ))
            {
                continue;
            }
            
            bool const spawnSuccess = Map[ x ].Tiles[ y ]->TrySpawn();
            if (!spawnSuccess)
            {
                Log::Error(
                    "Couldn't spawn level actors for MapTile at non-empty point ({0},{1}).",
                    x, y
                );
                return false;
            }
        }
    }
    
    return true;
}


// FWallSegment
///////////////
FWallSegment::FWallSegment( FIntPoint const start, FIntPoint const end ) :
    FIntPointPair( start, end )
{
    checkf(
        this->IsValid( true ),
        TEXT("The map points %s do not define a valid horizontal or vertical wall segment."),
        *ToString()
    );
    
    // Make sure the start->end points are left->right or top->bottom
    if (IsVertical())
    {
        if (Second.Y < First.Y)
        {
            Swap( First, Second );
        }
    }
    else if (Second.X < First.X)
    {
        Swap( First, Second );
    }
}

TArray<FIntPointPair> FWallSegment::GetAdjacentMapPoints() const
{
    TArray<FIntPointPair> adjacentPoints;
    adjacentPoints.Reserve( GetLength() );
    
    if (IsHorizontal())
    {
        for (int32 x = First.X, y = First.Y; x < Second.X; ++x)
        {
            adjacentPoints.Emplace( FIntPoint{x, (y-1)}, FIntPoint{ x, y } );
        }
        
    }
    else
    {
        for (int32 x = First.X, y = First.Y; y < Second.Y; ++y)
        {
            adjacentPoints.Emplace( FIntPoint{ (x-1), y }, FIntPoint{ x, y } );
        }
    }
    
    return adjacentPoints;
}
