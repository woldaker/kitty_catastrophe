// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
// KC
#include "Actors/Lure.h"
#include "Enums/ELure.h"
#include "Inventory.generated.h"


UCLASS(BlueprintType, Category="State", meta=(DisplayName="Inventory", ToolTip="Contains all available lures/deterrents and associated functionality."))
class KITTYCATASTROPHE_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UInventory();

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Add Lure", ToolTip="Add given number of lures of given type to inventory.  Defaults to one if no number given."))
	void AddLure(ELure const lureType, int32 const amount = 1);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Remove Lure", ToolTip="Remove given number of lures of given type from inventory.  Defaults to one if no number given."))
	void RemoveLure(ELure const lureType, int32 const amount = 1);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Get Active Lure Type", ToolTip="Gets the currently active lure type."))
	ELure const& GetActiveLureType() const;

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Set Active Lure Type", ToolTip="Sets the currently active lure to type given."))
	void SetActiveLureType(ELure const lureType);

	UFUNCTION(BlueprintCallable, Category="State", meta=(DisplayName="Get Available Lure Types", ToolTip="Returns an array of all lure types for which this player currently owns at least one."))
	TSet<ELure> const& GetAvailableLureTypes() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="State", meta=(DisplayName="Lure Tallies", ToolTip="Keeps count of how many of each type of lure the player currently has in inventory."))
    TMap<ELure, int32> LureTallies = {};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter=GetActiveLureType, Category="State", meta=(DisplayName="Active Lure Type", ToolTip="The type of lure that is currently selected to be dropped."))
    ELure ActiveLureType = ELure::DEFAULT;

	// Convenience purposes, so we don't have to compute it at runtime over and over:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter=GetAvailableLureTypes, Category="State", meta=(DisplayName="Available Lure Types", ToolTip="A list of lure types for which this player currently owns at least one."))
    TSet<ELure> AvailableLureTypes = {ELure::DEFAULT};
};


// INLINE DEFINITIONS
/////////////////////
inline ELure const& UInventory::GetActiveLureType() const
{
    return ActiveLureType;
}

inline TSet<ELure> const& UInventory::GetAvailableLureTypes() const
{
    return AvailableLureTypes;
}
