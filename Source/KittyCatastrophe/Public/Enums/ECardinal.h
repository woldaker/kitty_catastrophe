// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreTypes.h"
#include "Math/Rotator.h"


namespace Cardinal {
namespace /*Cardinal::*/ Private {
constexpr TCHAR const* NAME[] = {
    TEXT("North"),
    TEXT("East"),
    TEXT("South"),
    TEXT("West"),
    
    TEXT("")
};
} //ns Cardinal::Private
} //ns Cardinal


UENUM(BlueprintType)
enum class ECardinal : uint8
{
    NORTH = 0
        UMETA(DisplayName=Cardinal::Private::NAME[0]),
	EAST
        UMETA(DisplayName=Cardinal::Private::NAME[1]),
    SOUTH
        UMETA(DisplayName=Cardinal::Private::NAME[2]),
    WEST
        UMETA(DisplayName=Cardinal::Private::NAME[3]),
    
	MAX             UMETA(Hidden),
    RANGE_FIRST = 0 UMETA(Hidden),
    RANGE_LAST  = 3 UMETA(Hidden)
};
ENUM_RANGE_BY_FIRST_AND_LAST( ECardinal, ECardinal::RANGE_FIRST, ECardinal::RANGE_LAST )

namespace Cardinal {
constexpr uint8 DIRECTION_VALUE_MIN  = static_cast<uint8>(ECardinal::RANGE_FIRST);
constexpr uint8 DIRECTION_VALUE_MAX  = static_cast<uint8>(ECardinal::RANGE_LAST);
constexpr uint8 NUM_DIRECTION_VALUES = static_cast<uint8>(ECardinal::MAX);

// NORTH = -Y
// EAST  = +X
// SOUTH = +Y
// WEST  = -X
//WARNING: FRotator's stupid ass constructor has arg order { Y, X, Z }!!!
FRotator const ROTATOR_NORTH = { -90.0f, 0.0f, -90.0f };
FRotator const ROTATOR_EAST  = { -90.0f, 0.0f,   0.0f };
FRotator const ROTATOR_SOUTH = { -90.0f, 0.0f,  90.0f };
FRotator const ROTATOR_WEST  = {  90.0f, 0.0f,   0.0f };

bool IsValid( ECardinal const direction );
constexpr TCHAR const* GetName( ECardinal const direction );

FVector GetUnitVector( ECardinal const direction );
FRotator GetRotator( ECardinal const direction );

ECardinal GetDirectionTurned( ECardinal const direction, int32 const num90DegTurns );
ECardinal GetDirectionClockwise( ECardinal const direction );
ECardinal GetDirectionCounterClockwise( ECardinal const direction );
ECardinal GetDirectionOpposite( ECardinal const direction );
} //ns Cardinal


// INLINE DEFINITIONS
/////////////////////
inline constexpr TCHAR const* Cardinal::GetName( ECardinal const direction )
{ return Private::NAME[ static_cast<uint8>(direction) ]; }


inline FVector Cardinal::GetUnitVector( ECardinal const direction )
{
    switch (direction)
    {
    case ECardinal::NORTH:
        return { 0.0f, -1.0f, 0.0f };
    case ECardinal::EAST:
        return { 1.0f, 0.0f, 0.0f };
    case ECardinal::SOUTH:
        return { 0.0f, 1.0f, 0.0f };
    case ECardinal::WEST:
        return { -1.0f, 0.0f, 0.0f };
    default:
        checkNoEntry();
        return FVector::ZeroVector;
    }
}


inline FRotator Cardinal::GetRotator( ECardinal const direction )
{
    switch (direction)
    {
    case ECardinal::NORTH:
        return Cardinal::ROTATOR_NORTH;
    case ECardinal::EAST:
        return Cardinal::ROTATOR_EAST;
    case ECardinal::SOUTH:
        return Cardinal::ROTATOR_SOUTH;
    case ECardinal::WEST:
        return Cardinal::ROTATOR_WEST;
    default:
        checkNoEntry();
        return FRotator::ZeroRotator;
    }
}


inline ECardinal Cardinal::GetDirectionClockwise( ECardinal const direction )
{ return Cardinal::GetDirectionTurned( direction, 1 ); }


inline ECardinal Cardinal::GetDirectionCounterClockwise( ECardinal const direction )
{ return Cardinal::GetDirectionTurned( direction, -1 ); }


inline ECardinal Cardinal::GetDirectionOpposite( ECardinal const direction )
{ return Cardinal::GetDirectionTurned( direction, 2 ); }
