// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "LevelGeneratorSubsystem.h"
#include "FloorSection.h"
#include "FloorSectionMap.h"
#include "Utils/Log.h"

/*
void ULevelGeneratorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

}


void ULevelGeneratorSubsystem::Deinitialize()
{

}
*/


void ULevelGeneratorSubsystem::LoadLevel(UFloorSectionMap* level)
{
    if (!level)
    {
        Log::Error("Cannot load level!");
        return;
    }

    FIntPointPair const level_bounds = level->GetBoundingBox();
    FIntPoint const& lower = level_bounds.Lower;
    FIntPoint const& upper = level_bounds.Upper;

    for (int32 x = lower.X; x < upper.X; ++x)
    {
        for (int32 y = lower.Y; y < upper.Y; ++y)
        {
            FIntPoint point(x, y);

            if (level->GetMap().Contains(point) && level->GetMap()[point] != nullptr)
            {
                Log::Info("level has non-blank point at ({0}, {1})!", x, y);
            }
        }
    }

    OnLevelLoaded.Broadcast();
}


void ULevelGeneratorSubsystem::ClearLevel()
{
    for (AActor* actor : Actors)
    {
        actor->Destroy();
    }
}
