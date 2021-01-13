// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "Containers/UnrealString.h"
#include "Engine/EngineTypes.h"
#include "Math/IntPoint.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"


namespace KC {
namespace /*KC::*/ LEVEL {
bool IsValidLevelNumber( int32 const levelNumber );

constexpr int32 NUMBER_MIN = 1;
constexpr int32 NUMBER_MAX = 99;
constexpr int32 NUMBER_UNDEFINED = (NUMBER_MIN - 1);


namespace /*KC::LEVEL::*/ MAP {
// The min/max for X and Y of any point in a LevelMap.
constexpr int32 POINT_MIN = 0;
constexpr int32 POINT_MAX = 99;

bool IsValidPoint( FIntPoint const point );
bool IsValidPoint( int32 const x, int32 const y );

constexpr int32 LENGTH_MIN = 1;
constexpr int32 LENGTH_MAX = POINT_MAX - POINT_MIN;

bool IsValidLength( int32 const length );


namespace /*KC::LEVEL::MAP::*/ FILE {
FString ConstructPath( int32 const levelNumber );
constexpr TCHAR const* PREFIX = TEXT("Level_");


namespace /*KC::LEVEL::MAP::FILE::*/ KEYVAL {
bool IsValidKey( FString const& key );

constexpr TCHAR const* LITTERBOX  = TEXT("litterbox");
constexpr TCHAR const* FOODTROUGH = TEXT("foodtrough");
constexpr TCHAR const* WALL       = TEXT("wall");
} //ns KC::LEVEL::MAP::FILE::KEYVAL
} //ns KC::LEVEL::MAP::FILE


namespace /*KC::LEVEL::MAP::*/ TILE {
constexpr float UNIT_EXTENT_UNDEFINED = -1.0;


namespace /*KC::LEVEL::MAP::TILE::*/ ATTACH_RULES {
constexpr EAttachmentRule LOCATION = EAttachmentRule::KeepRelative;
constexpr EAttachmentRule ROTATION = EAttachmentRule::KeepRelative;
constexpr EAttachmentRule SCALE    = EAttachmentRule::KeepRelative;

constexpr bool WELD = false;

FAttachmentTransformRules const ALL { LOCATION, ROTATION, SCALE, WELD };
} //ns KC::LEVEL::MAP::TILE::ATTACH_RULES


namespace /*KC::LEVEL::MAP::TILE::*/ BOUNDS {
// The thickness of a MapTile compared to its width/height:
constexpr float NORMAL_TO_PLANE_LENGTH_RATIO = 0.1f;
} //ns KC::LEVEL::MAP::TILE::BOUNDS


namespace /*KC::LEVEL::MAP::TILE::*/ WALL {
// The amount by which a basic Wall section will need to be "stretched" along the vertical axis
constexpr float HEIGHT_SCALE = 3.0f;
} //ns KC::LEVEL::MAP::TILE::WALL


} //ns KC::LEVEL::MAP::TILE
} //ns KC::LEVEL::MAP
} //ns KC::LEVEL
} //ns KC



// INLINE DEFINITIIONS
//////////////////////
inline bool KC::LEVEL::IsValidLevelNumber( int32 const levelNumber )
{ return FMath::IsWithinInclusive( levelNumber, LEVEL::NUMBER_MIN, LEVEL::NUMBER_MAX ); }

inline bool KC::LEVEL::MAP::IsValidPoint( FIntPoint const point )
{
    return FMath::IsWithinInclusive( point.X, MAP::POINT_MIN, MAP::POINT_MAX ) &&
           FMath::IsWithinInclusive( point.Y, MAP::POINT_MIN, MAP::POINT_MAX );
}

inline bool KC::LEVEL::MAP::IsValidPoint( int32 const x, int32 const y )
{ return MAP::IsValidPoint( {x,y} ); }

inline bool KC::LEVEL::MAP::IsValidLength( int32 const length )
{ return FMath::IsWithinInclusive( length, MAP::LENGTH_MIN, MAP::LENGTH_MAX ); }

inline bool KC::LEVEL::MAP::FILE::KEYVAL::IsValidKey( FString const& key )
{
    return (key == KEYVAL::LITTERBOX)  ||
           (key == KEYVAL::FOODTROUGH) ||
           (key == KEYVAL::WALL);
}


// MISC
///////
static_assert(
    (KC::LEVEL::NUMBER_MIN < KC::LEVEL::NUMBER_MAX),
    TEXT("LEVEL::NUMBER_MIN shouldn't be greater than LEVEL::NUMBER_MAX")
);
static_assert(
    (KC::LEVEL::MAP::POINT_MIN < KC::LEVEL::MAP::POINT_MAX),
    TEXT("MAP::POINT_MIN shouldn't be greater than MAP::POINT_MAX")
);
static_assert(
    (KC::LEVEL::MAP::LENGTH_MIN < KC::LEVEL::MAP::LENGTH_MAX),
    TEXT("MAP::LENGTH_MIN shouldn't be greater than MAP::LENGTH_MAX")
);
