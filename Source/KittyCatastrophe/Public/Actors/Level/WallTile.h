// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
// KC
#include "Actors/Level/MapTile.h"
#include "Enums/ECardinal.h"
#include "WallTile.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, Category="Map|Tiles", ClassGroup=(Map,HealthProxy), meta=(IsBlueprintBase="true", DisplayName="Wall Tile", ToolTip="One grid-unit of wall in a Level."))
class KITTYCATASTROPHE_API AWallTile : public AMapTile
{
	GENERATED_BODY()
public:
    AWallTile();
    
    UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Orient", ToolTip="Rotates the actor so that its renderable surface is facing the direction required for viewing it when looking toward the given direction."))
    void Orient( ECardinal const direction );
};
