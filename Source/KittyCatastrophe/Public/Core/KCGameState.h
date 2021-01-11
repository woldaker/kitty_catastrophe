// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
// KC
#include "Config/Constants/Level.h"
#include "KCGameState.generated.h"


UCLASS()
class KITTYCATASTROPHE_API AKCGameState : public AGameState
{
	GENERATED_BODY()
public:
    UFUNCTION(meta=(DisplayName="Get Current Level Number", ToolTip="Returns the current level number."))
    int32 GetCurrentLevelNumber() const;

    UFUNCTION(meta=(DisplayName="Get Next Level Number", ToolTip="Returns the level number which is next in sequence from the current level number."))
    int32 GetNextLevelNumber() const;

    UFUNCTION(meta=(DisplayName="Set Current Level Number", ToolTip="Sets the current level number.  Does not load it, though."))
    void SetCurrentLevelNumber(
        UPARAM(DisplayName="New Level Number")
        int32 const newLevelNumber
    );
    
    UFUNCTION(meta=(DisplayName="Increment Current Level Number", ToolTip="Increments the current level number by one."))
    void IncrementCurrentLevelNumber();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Current Level Number", ToolTip="The level number for the current level, loaded from a LevelMap."))
    int32 CurrentLevelNumber = KC::LEVEL::NUMBER_UNDEFINED;
};


inline int32 AKCGameState::GetCurrentLevelNumber() const { return CurrentLevelNumber; }
inline int32 AKCGameState::GetNextLevelNumber() const    { return GetCurrentLevelNumber() + 1; }
inline void  AKCGameState::IncrementCurrentLevelNumber() { ++CurrentLevelNumber; }
