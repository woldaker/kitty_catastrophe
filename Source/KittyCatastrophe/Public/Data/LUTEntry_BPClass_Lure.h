// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
// KC
#include "LUTEntry_BPClass_Lure.generated.h"

class ALure;


USTRUCT(BlueprintType, meta=(DisplayName="Lookup Table Entry: Blueprint Class, Lure", ToolTip="For fetching a specific (blueprinted) subclass of Lure, by name."))
struct FLUTEntry_BPClass_Lure : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="Blueprint Class"))
    TSubclassOf<ALure> BPClass;
};
