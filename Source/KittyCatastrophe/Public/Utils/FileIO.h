// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FileIO.generated.h"


UCLASS()
class KITTYCATASTROPHE_API UFileIO : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="File I/O")
    static bool TryLoadFileToString(FString& OutContents_, FString const& RelativePath_);

    UFUNCTION(BlueprintCallable, Category="File I/O")
    static bool TryLoadFileToStringArray(TArray<FString>& OutContents_, FString const& RelativePath_);
};
