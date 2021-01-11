// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
// KC
#include "LUTEntry_BPClass_FloorTile.generated.h"

class AFloorTile;


USTRUCT(BlueprintType, meta=(DisplayName="Lookup Table Entry: Blueprint Class, FloorTile", ToolTip="For fetching a specific (blueprinted) subclass of FloorTile, by name."))
struct FLUTEntry_BPClass_FloorTile : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="Blueprint Class"))
    TSubclassOf<AFloorTile> BPClass;
};
