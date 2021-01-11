// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
// KC
#include "Actors/Level/MapTile.h"
#include "CeilingTile.generated.h"


UCLASS(NotBlueprintable, BlueprintType, Category="Map|Tiles", ClassGroup=(Map,HealthProxy), meta=(IsBlueprintBase="false", DisplayName="Ceiling Tile", ToolTip="One grid-unit of ceiling in a Level."))
class KITTYCATASTROPHE_API ACeilingTile : public AMapTile
{
    GENERATED_BODY()
public:
    ACeilingTile();
    
    void Init( float const height );
};
