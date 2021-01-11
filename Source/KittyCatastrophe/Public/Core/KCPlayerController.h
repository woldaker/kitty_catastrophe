// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// KC
#include "KCPlayerController.generated.h"

class ALure;
class UDataTable;


UCLASS(BlueprintType, Blueprintable, meta=(ShortTooltip="Custom Player Controller for handling touch inputs."))
class KITTYCATASTROPHE_API AKCPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AKCPlayerController();

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnTouchPressed();

	UFUNCTION()
	void OnTouchReleased();

protected:
	UPROPERTY(BlueprintReadOnly)
	ALure* SpawnedLure = nullptr;

	UDataTable* DT_BPLure = nullptr;

	FTimerHandle Timer_UpdateSpawnLocation;

	void UpdateSpawnLocation();
};
