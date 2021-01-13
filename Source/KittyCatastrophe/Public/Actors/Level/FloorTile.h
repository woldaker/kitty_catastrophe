// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
// KC
#include "Actors/Level/MapTile.h"
#include "FloorTile.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, Category="Map|Tiles", ClassGroup=(Map,HealthProxy), Transient, meta=(IsBlueprintBase="true", DisplayName="Floor Tile", ToolTip="One grid-unit of floor in a Level."))
class KITTYCATASTROPHE_API AFloorTile : public AMapTile
{
    GENERATED_BODY()
};

