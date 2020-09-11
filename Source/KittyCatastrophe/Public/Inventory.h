// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Containers/Set.h"
#include "Containers/Map.h"
#include "UObject/Object.h"
#include "Lure.h"
#include "Inventory.generated.h"


UCLASS(BlueprintType, Category="State")
class KITTYCATASTROPHE_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UInventory();

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Add Lure", ToolTip="Add given number of lures of given type to inventory.  Defaults to one if no number given."))
	void AddLure(ELureType const& lure_type, int32 const amount = 1);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Remove Lure", ToolTip="Remove given number of lures of given type from inventory.  Defaults to one if no number given."))
	void RemoveLure(ELureType const& lure_type, int32 const amount = 1);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Get Active Lure Type", ToolTip="Gets the currently active lure type."))
	ELureType GetActiveLureType() const;

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Set Active Lure Type", ToolTip="Sets the currently active lure to type given."))
	void SetActiveLureType(ELureType const& lure_type);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Get Available Lure Types", ToolTip="Returns an array of all lure types for which this player currently owns at least one."))
	TSet<ELureType> const& GetAvailableLureTypes() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State", meta=(DisplayName="Number of Lures Owned by Type", ToolTip="Keeps count of how many of each type of lure the player currently has in inventory."))
	TMap<ELureType, int32> LureCountTable;

	// Convenience purposes, so we don't have to compute it at runtime over and over:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta=(DisplayName="Available Lure Types", ToolTip="A list of lure types for which this player currently owns at least one."))
	TSet<ELureType> AvailableLureTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", meta=(DisplayName="Active Lure Type", ToolTip="The type of lure that is currently selected to be dropped."))
	ELureType ActiveLureType;

	static int32 const INFINITE_SUPPLY = -1;
};
