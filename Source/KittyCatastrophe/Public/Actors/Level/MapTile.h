// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
// KC
#include "Actors/Level/DamageReceiver.h"
#include "Config/Constants/Level.h"
#include "MapTile.generated.h"

class UStaticMeshComponent;


UCLASS(Abstract, NotBlueprintable, BlueprintType, Category="Map|Tiles", ClassGroup=(Map,HealthProxy), meta=(IsBlueprintBase="false", DisplayName="Map Tile", ToolTip="One tile of the map, either a floor, wall, or ceiling, which occupies 1 map grid unit."))
class KITTYCATASTROPHE_API AMapTile : public ADamageReceiver
{
	GENERATED_BODY()
public:
    AMapTile();
    
    UFUNCTION(BlueprintCallable, Category="Map|Constants", meta=(DisplayName="Get Unit Extent", ToolTip="Returns the extent of the Plane mesh.  In other words, the shortest distance from the middle of the plane to one of its edges."))
    static UPARAM(DisplayName="Unit Length") float GetUnitExtent();
    
    UFUNCTION(BlueprintCallable, Category="Map|State", meta=(DisplayName="Is Unit Extent Set", ToolTip="Returns true if the static MapTile::UnitExtent property has been initialized."))
    static UPARAM(DisplayName="Is Defined") bool IsUnitExtentSet();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Plane", ToolTip="The plane mesh for this MapTile's surface."))
    UStaticMeshComponent* Plane = nullptr;
    
    virtual void InitOverlapBounds() override;

    static float UnitExtent;
};


// INLINE DEFINITIONS
inline float AMapTile::GetUnitExtent()
{
    return AMapTile::UnitExtent;
}

inline bool AMapTile::IsUnitExtentSet()
{
    namespace MAPTILE = KC::LEVEL::MAP::TILE;
    return (AMapTile::UnitExtent > FMath::Max(MAPTILE::UNIT_EXTENT_UNDEFINED, 0.0f));
}
