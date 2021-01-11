// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Utils/StringParser.h"

#include "Containers/Array.h"
#include "Misc/CString.h"

#include "Utils/Log.h"


/*
KCLog: Display: String '(6' is not an IntPoint: must be in the form '(x,y)'.
KCLog: Warning: String '(6' is not an IntPoint: must be in the form '(x,y)'.
KCLog: Display: In IntPointRange string '(5,4):(6:4)': substring '(6' is not a valid IntPoint.  Must be in the form '(X,Y)'.
KCLog: Warning: In IntPointRange string '(5,4):(6:4)': substring '(6' is not a valid IntPoint.  Must be in the form '(X,Y)'.
KCLog: Display: String '4)' is not an IntPoint: must be in the form '(x,y)'.
KCLog: Warning: String '4)' is not an IntPoint: must be in the form '(x,y)'.
KCLog: Display: In IntPointRange string '(5,4):(6:4)': substring '4)' is not a valid IntPoint.  Must be in the form '(X,Y)'.
KCLog: Warning: In IntPointRange string '(5,4):(6:4)': substring '4)' is not a valid IntPoint.  Must be in the form '(X,Y)'.
KCLog: Display: Invalid val string: '(5,4):(6:4)'.
KCLog: Error: Invalid val string: '(5,4):(6:4)'.
KCLog: Display: Could not parse contents of Map file 'KittyCatastrophe/Levels/Maps/Level_01'
KCLog: Error: Could not parse contents of Map file 'KittyCatastrophe/Levels/Maps/Level_01'
KCLog: Display: Error loading LevelMap for level 1.
KCLog: Error: Error loading LevelMap for level 1.
 */


bool StringParser::TryKeyVal(FString const& str, FString& OutKey, FString& OutVal)
{
    static constexpr TCHAR const* delim = TEXT("=");
    TArray<FString> parts;
  
    if (str.ParseIntoArray(parts, delim, true) != 2)
    {
        Log::Warn("String '{0}' is not a key/val pair: must be in the form 'key=value'.", str);
        return false;
    }

    OutKey = parts[0];
    OutVal = parts[1];
    return true;
}


bool StringParser::TryIntPoint(FString const& str, FIntPoint& OutPoint)
{
    static TCHAR const* delims[] = {TEXT("("), TEXT(","), TEXT(")")};
    TArray<FString> parts;
  
    if (str.ParseIntoArray(parts, delims, 3, true) != 2)
    {
        Log::Warn("String '{0}' is not an IntPoint: must be in the form '(x,y)'.", str);
        return false;
    }

    if (!parts[0].IsNumeric() || !parts[1].IsNumeric())
    {
      Log::Warn("String '{0}' is not an IntPoint: must be in the form '(x,y)', and x and y must contain only numbers.", str);
      return false;
    }
  
    OutPoint.X = FCString::Atoi(*parts[0]);
    OutPoint.Y = FCString::Atoi(*parts[1]);
    return true;
}


bool StringParser::TryIntPointRange(FString const& str, TArray<FIntPoint>& OutPoints)
{
    static constexpr TCHAR const* delim = TEXT(":");
    
    TArray<FString> pointStrings;
    int32 const numPoints = str.ParseIntoArray(pointStrings, delim, true);
    
    if (numPoints <= 1)
    {
        Log::Warn("String '{0}' is not a valid IntPointRange: must be in the form '(X1,Y1):(X2,Y2)[:(Xn,Yn)...]'.", str);
        return false;
    }
    
    OutPoints.Empty();
    bool success = true;
    
    for (FString const& pointString : pointStrings)
    {
        FIntPoint point;
        if (TryIntPoint(pointString, point))
        {
            OutPoints.Add(point);
        }
        else
        {
            Log::Warn("In IntPointRange string '{0}': substring '{1}' is not a valid IntPoint.  Must be in the form '(X,Y)'.", str, pointString);
            
            success = false;
        }
    
    }
    
    return success;
}
