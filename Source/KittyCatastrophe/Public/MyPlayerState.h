// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class UInventory;


UCLASS()
class KITTYCATASTROPHE_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMyPlayerState();

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Get Inventory", ToolTip="Returns a pointer to this player's current inventory."))
	UInventory* GetInventory();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State", meta=(ToolTip="This player's current inventory."))
	UInventory* Inventory;
};
