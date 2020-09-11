// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Containers/Map.h"
#include "Engine/DataAsset.h"
#include "Math/IntPoint.h"
#include "Templates/SubclassOf.h"
#include "FloorSectionMap.generated.h"

class AFloorSection;

USTRUCT(BlueprintType)
struct FIntPointPair
{
    GENERATED_BODY()

    FIntPoint Lower = {0,0};
    FIntPoint Upper = {0,0};
};


UCLASS(BlueprintType, meta=(DisplayName="FloorSection Map"))
class UFloorSectionMap : public UDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DisplayName="Get Bounding Box"))
    FIntPointPair GetBoundingBox() const;

    UFUNCTION(BlueprintCallable, CallInEditor, meta=(DisplayName="Fill Bounding Box", ToolTip="Any coordinates without a matching value in the Map will be created and NULL-initialized."))
    void FillBoundingBox();

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Map (Read-Only)"))
    TMap<FIntPoint, TSubclassOf<AFloorSection>> const& GetMap() const;
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Floor Map"))
    TMap<FIntPoint, TSubclassOf<AFloorSection>> Map;
};
