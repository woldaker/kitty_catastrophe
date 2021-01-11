// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Containers/UnrealString.h"
#include "Math/IntPoint.h"


namespace StringParser {

bool TryKeyVal(FString const& str, FString& OutKey, FString& OutVal);
bool TryIntPoint(FString const& str, FIntPoint& OutPoint);
bool TryIntPointRange(FString const& str, TArray<FIntPoint>& OutPoints);

} //ns StringParser
