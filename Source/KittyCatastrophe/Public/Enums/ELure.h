// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreTypes.h"
#include "Misc/EnumRange.h"


namespace Lure {
namespace /*Lure::*/ Private {
constexpr TCHAR const* NAME[] = {
    TEXT("Empty"),
    
    // Lures
    TEXT("Yarnball"),
    TEXT("Rubber Mouse"),
    TEXT("Kleenex Box"),
    // Deterrents
    TEXT("Toy Robot"),
    TEXT("Vacuum Cleaner"),
    
    TEXT("")
};
} //ns Lure::Private
} //ns Lure


UENUM(BlueprintType)
enum class ELure : uint8
{
    NONE = 0
        UMETA(DisplayName=Lure::Private::NAME[0]),
	// Lures
	YARNBALL
        UMETA(DisplayName=Lure::Private::NAME[1]),
	RUBBER_MOUSE
        UMETA(DisplayName=Lure::Private::NAME[2]),
	KLEENEX_BOX
        UMETA(DisplayName=Lure::Private::NAME[3]),
	// Deterrents
	TOY_ROBOT
        UMETA(DisplayName=Lure::Private::NAME[4]),
	VACUUM_CLEANER
        UMETA(DisplayName=Lure::Private::NAME[5]),

	MAX             UMETA(Hidden),
    DEFAULT     = 1 UMETA(Hidden),
    RANGE_FIRST = 1 UMETA(Hidden),
    RANGE_LAST  = 5 UMETA(Hidden)
};
ENUM_RANGE_BY_FIRST_AND_LAST( ELure, ELure::RANGE_FIRST, ELure::RANGE_LAST )


namespace Lure {
constexpr TCHAR const* GetName( ELure const lureType );

constexpr bool IsValid( ELure const lureType );
constexpr bool IsAbstract( ELure const lureType );
} //ns Lure


// INLINE DEFINITIONS
/////////////////////
inline constexpr TCHAR const* Lure::GetName( ELure const lureType )
{
    return Private::NAME[ static_cast<uint8>(lureType) ];
}

inline constexpr bool Lure::IsValid( ELure const lureType )
{
    return (lureType != ELure::MAX);
}

inline constexpr bool Lure::IsAbstract( ELure const lureType )
{
    return !Lure::IsValid( lureType ) || (lureType == ELure::NONE);
}


// STATIC ASSERTIONS
////////////////////
static_assert(
    !Lure::IsAbstract( ELure::DEFAULT ),
    TEXT("ELure::DEFAULT cannot be set to ELure::NONE or ELure::MAX")
);

static_assert(
    !Lure::IsAbstract( ELure::RANGE_FIRST ),
    TEXT("ELure::RANGE_FIRST cannot be set to ELure::NONE or ELure::MAX")
);

static_assert(
    !Lure::IsAbstract( ELure::RANGE_LAST ),
    TEXT("ELure::RANGE_LAST cannot be set to ELure::NONE or ELure::MAX")
);
