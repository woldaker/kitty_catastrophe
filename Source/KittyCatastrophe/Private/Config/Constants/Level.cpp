// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Config/Constants/Level.h"
// Engine
#include "Misc/AssertionMacros.h"
// KC
//#include "Config/Constants/Log.h"
#include "Config/Constants/Path.h"


FString KC::LEVEL::MAP::FILE::ConstructPath(int32 const levelNumber)
{
    static FString const PATH_PREFIX = PATH::LEVELMAPS + FILE::PREFIX;

    checkf( LEVEL::IsValidLevelNumber(levelNumber),
        TEXT(/*KCINFO*/ "Level number given (%d) is not in the valid range [%d - %d] (inclusive)."),
        levelNumber, LEVEL::NUMBER_MIN, LEVEL::NUMBER_MAX
    );

    return PATH_PREFIX + FString::Printf(TEXT("%02d"), levelNumber);
}
