// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ALure;
class UDataTable;

UCLASS(BlueprintType, Blueprintable, meta=(ShortTooltip="Custom Player Controller for handling touch inputs."))
class KITTYCATASTROPHE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AMyPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnTouchPressed();

	UFUNCTION()
	void OnTouchReleased();

protected:
	UPROPERTY(BlueprintReadOnly)
	ALure* SpawnedLure;

	UDataTable* LureClasses;

	FTimerHandle TimerHandleUpdateSpawnLocation;

	void UpdateSpawnLocation();
};
