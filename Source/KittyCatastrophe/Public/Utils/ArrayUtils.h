// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Containers/Array.h"
//#include "Templates/Casts.h"
#include "Templates/UnrealTypeTraits.h"


namespace ArrayUtils {

template<typename Target, typename Original>
TArray<Target*> ConvertPointerType (TArray<Original*> const& original)
{
    static_assert(TIsDerivedFrom<Target, Original>::IsDerived, TEXT("Return type is not a subclass of parameter."));
    
    Original *const * originalArray = original.GetData();
    if (!originalArray)
    {
        return {};
    }
    
    Target* targetFirstElement = Cast<Target>(*originalArray);
    return { &targetFirstElement, original.Num() };
    /*
    TArray<Target*> converted
    converted.Reset(arr.Num());
    
    for (Original* ptr : arr)
    {
        Target* target = Cast<Target>(ptr);
        
        if (target)
        {
            converted.Add(target);
        }
    }
     */
}

} // END ArrayUtils
