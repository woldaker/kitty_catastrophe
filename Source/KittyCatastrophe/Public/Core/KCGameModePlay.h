// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "KCGameModePlay.generated.h"


UCLASS()
class KITTYCATASTROPHE_API AKCGameModePlay : public AGameMode
{
	GENERATED_BODY()
public:
    AKCGameModePlay();

    //virtual void InitGame(FString const& mapName, FString const& options, FString& errorMessage) override;

    virtual void InitGameState() override;

protected:
    bool ReadyToStartMatch();

private:
    bool bLevelGenerated = false;
};
