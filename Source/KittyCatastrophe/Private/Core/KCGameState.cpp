// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Core/KCGameState.h"
// KC
//#include "Config/Constants/Log.h"


void AKCGameState::SetCurrentLevelNumber(int32 const newLevelNumber)
{
    checkf(KC::LEVEL::IsValidLevelNumber(newLevelNumber),
        TEXT(/*KCINFO*/ "Invalid level number '%d': value must be between '%d' and '%d' (inclusive)."), newLevelNumber, KC::LEVEL::NUMBER_MIN, KC::LEVEL::NUMBER_MAX
    );

    CurrentLevelNumber = newLevelNumber;
}
