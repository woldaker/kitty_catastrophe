// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Config="Game", NotPlaceable, BlueprintType, Blueprintable, Transient, HideCategories=(Info, Rendering, MovementReplication, Replication, Actor), meta=(ShortTooltip="Overrides GameModeBase with a custom Player Controller."))
class KITTYCATASTROPHE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();
};
