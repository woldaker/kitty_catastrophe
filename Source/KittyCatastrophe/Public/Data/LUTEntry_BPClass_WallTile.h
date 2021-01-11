// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
// KC
#include "LUTEntry_BPClass_WallTile.generated.h"

class AWallTile;


USTRUCT(BlueprintType, meta=(DisplayName="Lookup Table Entry: Blueprint Class, WallTile", ToolTip="For fetching a specific (blueprinted) subclass of WallTile, by name."))
struct FLUTEntry_BPClass_WallTile : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="Blueprint Class"))
    TSubclassOf<AWallTile> BPClass;
};
