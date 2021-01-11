// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Enums/EFloorTile.h"
#include "Utils/Log.h"


// FloorTile::Neighbors
//////////////////////////////

FloorTile::NeighborData::NeighborData(
    TArray<FString> const& mapData,
    int32 const x,
    int32 const y
) :
    Self ( NeighborData::ExtractChar( mapData,  x,     y    ) ),
    North( NeighborData::ExtractChar( mapData,  x   , (y-1) ) ),
    East ( NeighborData::ExtractChar( mapData, (x+1),  y    ) ),
    South( NeighborData::ExtractChar( mapData,  x   , (y+1) ) ),
    West ( NeighborData::ExtractChar( mapData, (x-1),  y    ) )
{}


TCHAR FloorTile::NeighborData::ExtractChar(
    TArray<FString> const& mapData,
    int32 const x,
    int32 const y
) {
    // Validity check and value sanitization:
    if (// No negative indices:
        (x < 0) || (y < 0) ||
        // row-index/line-number check:
        (y >= mapData.Num()) ||
        // column/char index check:
        (x >= mapData[ y ].Len()) ||
        // empty char check:
        // In reverse (y,x) because data is an array of strings;
        //   Each string is a row, not a column.
        FloorTile::IsAbstract( mapData[ y ][ x ] )
    ) {
        return FloorTile::EMPTY_CHAR;
    }
    
    return mapData[ y ][ x ];
}
