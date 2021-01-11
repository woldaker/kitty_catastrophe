// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreTypes.h"
//#include "Containers/Array.h"
//#include "Containers/UnrealString.h"
// KC
#include "Enums/ECardinal.h"


namespace FloorTile {
namespace /*FloorTile::*/ Private {
//TODO: make NAME and MAPCHAR into TMap<FString, TCHAR>?  May not be able to be constexpr though...
constexpr TCHAR const* NAME[] = {
    TEXT("Empty"),
    
    TEXT("Carpet"),
    TEXT("Hardwood"),
    
    TEXT("")
};

constexpr TCHAR MAPCHAR[] = {
    ' ',
    
    'c',
    'h',
    
    '\0'
};
} //ns FloorTile::Private


struct /*FloorTile::*/ NeighborData
{
    NeighborData(
        TArray<FString> const& mapData,
        int32 const x,
        int32 const y
    );
    
    bool Is() const;
    bool IsVacant( ECardinal const direction ) const;

    TCHAR const Self;
    TCHAR const North;
    TCHAR const East;
    TCHAR const South;
    TCHAR const West;
    
private:
    static TCHAR ExtractChar( TArray<FString> const& mapData, int32 const x, int32 const y );
};
} //ns FloorTile


UENUM(BlueprintType)
enum class EFloorTile : uint8
{
    EMPTY = 0
        UMETA(DisplayName=FloorTile::Private::NAME[0]),
    
    CARPET
        UMETA(DisplayName=FloorTile::Private::NAME[1]),
    HARDWOOD
        UMETA(DisplayName=FloorTile::Private::NAME[2]),

	MAX UMETA(Hidden)
};


namespace FloorTile {
constexpr TCHAR EMPTY_CHAR = Private::MAPCHAR[ static_cast<uint8>(EFloorTile::EMPTY) ];

constexpr TCHAR GetChar( EFloorTile const floorType );

constexpr TCHAR const* GetName( EFloorTile const floorType );
constexpr TCHAR const* GetName( TCHAR const floorChar );

constexpr EFloorTile GetType( TCHAR const floorChar );

constexpr bool IsEmpty( EFloorTile const floorType );
constexpr bool IsEmpty( TCHAR const floorChar );

constexpr bool IsValid( EFloorTile const floorType );
constexpr bool IsValid( TCHAR const floorChar );

constexpr bool IsAbstract( EFloorTile const floorType );
constexpr bool IsAbstract( TCHAR const floorChar );
} //ns FloorTile


// INLINE DEFINITIONS
/////////////////////

// FloorTile::Neighbors
///////////////////////
inline bool FloorTile::NeighborData::IsVacant( ECardinal const direction ) const
{
    switch (direction)
    {
    case ECardinal::NORTH:
        return (North == FloorTile::EMPTY_CHAR);
    case ECardinal::EAST:
        return (East == FloorTile::EMPTY_CHAR);
    case ECardinal::SOUTH:
        return (South == FloorTile::EMPTY_CHAR);
    case ECardinal::WEST:
        return (West == FloorTile::EMPTY_CHAR);
    default:
        checkNoEntry();
        return true;
    }
}

inline constexpr TCHAR FloorTile::GetChar( EFloorTile const floorType )
{ return Private::MAPCHAR[ static_cast<uint8>(floorType) ]; }

inline constexpr TCHAR const* FloorTile::GetName( EFloorTile const floorType )
{ return Private::NAME[ static_cast<uint8>(floorType) ]; }

inline constexpr TCHAR const* FloorTile::GetName( TCHAR const floorChar )
{ return GetName( GetType( floorChar ) ); }


inline constexpr EFloorTile FloorTile::GetType( TCHAR const floorChar )
{
    using namespace Private;
    
    switch(floorChar)
    {
    case MAPCHAR[ static_cast<uint8>(EFloorTile::EMPTY) ]:
        return EFloorTile::EMPTY;
    
    case MAPCHAR[ static_cast<uint8>(EFloorTile::CARPET) ]:
        return EFloorTile::CARPET;
    case MAPCHAR[ static_cast<uint8>(EFloorTile::HARDWOOD) ]:
        return EFloorTile::HARDWOOD;
    
    case MAPCHAR[ static_cast<uint8>(EFloorTile::MAX) ]:
    default:
        return EFloorTile::MAX;
    }
}

inline constexpr bool FloorTile::IsEmpty( EFloorTile const floorType )
{ return (floorType == EFloorTile::EMPTY); }

inline constexpr bool FloorTile::IsEmpty( TCHAR const floorChar )
{ return IsEmpty( GetType( floorChar ) ); }

inline constexpr bool FloorTile::IsValid( EFloorTile const floorType )
{ return (floorType != EFloorTile::MAX); }

inline constexpr bool FloorTile::IsValid( TCHAR const floorChar )
{ return IsValid( GetType( floorChar ) ); }

inline constexpr bool FloorTile::IsAbstract( EFloorTile const floorType )
{ return !IsValid( floorType ) || IsEmpty( floorType ); }

inline constexpr bool FloorTile::IsAbstract( TCHAR const floorChar )
{ return IsAbstract( GetType( floorChar ) ); }
