// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "FloorSectionMap.h"
#include "FloorSection.h"
//#include "Utils/Log.h"


FIntPointPair UFloorSectionMap::GetBoundingBox() const
{
    FIntPointPair bounds;   // bounds.Lower will be set to the first (i.e. lowest integer-valued) NON-BLANK point in Map.
                            // bounds.Upper will be the opposite except it will be the first BLANK point OFF the Map.  Kinda like iterator::end().
    
    {
        TArray<TSubclassOf<AFloorSection>> values;
        Map.GenerateValueArray(values);

        // first test to see if there are even any valid values in the Map.  If not, just return.
        if (values.FilterByPredicate([](auto const& subclass) { return subclass != nullptr; }).Num() == 0)
        {
            return bounds;
        }
    }
    
    TArray<FIntPoint> keys;
    Map.GenerateKeyArray(keys);
        
    FIntPoint& lower = bounds.Lower;
    FIntPoint& upper = bounds.Upper;

    lower = keys[0];
    upper.X = lower.X + 1;
    upper.Y = lower.Y + 1;

    for (auto const& point_class_pair : Map)
    {
        FIntPoint const& point = point_class_pair.Key;

        if (point_class_pair.Value == nullptr)
        {
            continue;
        }

        if (upper.X <= point.X)
        {
            upper.X = (point.X + 1);
        }
        else if (lower.X > point.X)
        {
            lower.X = point.X;
        }

        if (upper.Y <= point.Y)
        {
            upper.Y = (point.Y + 1);
        }
        else if (lower.Y > point.Y)
        {
            lower.Y = point.Y;
        }
    }

    return bounds;
}


void UFloorSectionMap::FillBoundingBox()
{
    FIntPointPair const bounds = GetBoundingBox();
    FIntPoint index;

    for (int32 x = bounds.Lower.X; x < bounds.Upper.X; ++x)
    {
        for (int32 y = bounds.Lower.Y; y < bounds.Upper.Y; ++y)
        {
            index.X = x;
            index.Y = y;

            if (!Map.Contains(index))
            {
                Map.Add(index, nullptr);
            }
        }
    }
}


TMap<FIntPoint, TSubclassOf<AFloorSection>> const& UFloorSectionMap::GetMap() const
{
    return Map;
}
