// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreTypes.h"


namespace KittyFoot {
namespace /*KittyFoot::*/ Private {
constexpr TCHAR const* NAME[] = {
    TEXT("Front Left"),
    TEXT("Front Right"),
    TEXT("Back Left"),
    TEXT("Back Right"),
    
    TEXT("")
};
} //ns KittyFoot::Private
} //ns KittyFoot


UENUM(BlueprintType)
enum class EKittyFoot : uint8
{
	FRONT_LEFT = 0
        UMETA(DisplayName=KittyFoot::Private::NAME[0]),
	FRONT_RIGHT
        UMETA(DisplayName=KittyFoot::Private::NAME[1]),
	BACK_LEFT
        UMETA(DisplayName=KittyFoot::Private::NAME[2]),
	BACK_RIGHT
        UMETA(DisplayName=KittyFoot::Private::NAME[3]),

	MAX UMETA(Hidden)
};

namespace KittyFoot {
constexpr TCHAR const* GetName( EKittyFoot const foot );

constexpr bool IsValid( EKittyFoot const foot );
} //ns KittyFoot


// INLINE DEFINITIONS
/////////////////////
inline constexpr TCHAR const* KittyFoot::GetName( EKittyFoot const foot )
{ return Private::NAME[ static_cast<uint8>(foot) ]; }

inline constexpr bool KittyFoot::IsValid( EKittyFoot const foot )
{ return (foot != EKittyFoot::MAX); }
