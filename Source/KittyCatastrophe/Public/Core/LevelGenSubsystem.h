// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
// KC
#include "LevelGenSubsystem.generated.h"

class ULevelMap;


UCLASS(meta=(DisplayName="Level Generator Subsystem", ToolTip="World Subsystem used to load level map files and spawn them."))
class KITTYCATASTROPHE_API ULevelGenSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    ULevelGenSubsystem();
    
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//virtual void Deinitialize() override;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category="LevelGenSubsystem", meta=(DisplayName="Load Level", ToolTip="Attempts to load the Map file associated with the specified level from its corresponding LevelMap file into memory.  This process is internal to the Level Generator and does not load the level into the scene.  Returns true on success."))
    bool TryLoadLevel(int32 const levelNumber);
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category="LevelGenSubsystem", meta=(DisplayName="Load Next Level", ToolTip="Attempts to load the Map file associated with whatever level comes after the current level, or level 1 by default.  This process is internal to the Level Generator and does not load the level into the scene.  Returns true on success."))
    bool TryLoadNextLevel();
    
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoaded);

	UPROPERTY(BlueprintAssignable, Category="LevelGenSubsystem", meta=(DisplayName="On Level Loaded", ToolTip="Multicast delegate called when level is successfully loaded."))
	FLevelLoaded OnLevelLoaded;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelGenSubsystem", meta=(DisplayName="Level Map", ToolTip="Container for the currently loaded LevelMap file."))
    ULevelMap* LevelMap = nullptr;
};
