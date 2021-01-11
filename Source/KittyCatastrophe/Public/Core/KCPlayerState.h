// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

#include "Actors/Level/LevelHealthProxy.h"
#include "Config/Constants/HealthAndDamage.h"
#include "KCPlayerState.generated.h"

//class AController;
class UInventory;
class ILevelHealthProxy;


UCLASS()
class KITTYCATASTROPHE_API AKCPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AKCPlayerState();
    
    friend class ILevelHealthProxy;
    
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="State", meta=(DisplayName="Get Inventory", ToolTip="Returns a pointer to this player's current inventory."))
    UPARAM(DisplayName="Inventory")
    UInventory* GetInventory() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="State", meta=(DisplayName="Number of Kitties", ToolTip="Returns the total number of kitties in the current level."))
    UPARAM(DisplayName="Kitties")
    int32 NumKitties() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="State", meta=(DisplayName="Number of Kitties Yet to Poop", ToolTip="Returns the number of kitties in the current level that have not yet pooped."))
    UPARAM(DisplayName="Kitties Yet to Poop")
    int32 NumKittiesToPoop() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="State", meta=(DisplayName="Get Level Health", ToolTip="Returns the level's current Health."))
    UPARAM(DisplayName="Level Health")
    float GetLevelHealth() const;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", BlueprintGetter=GetInventory, meta=(DisplayName="Inventory", ToolTip="The player's current inventory."))
    UInventory* Inventory = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", BlueprintGetter=NumKitties, meta=(DisplayName="Number of Kitties", ToolTip="Total number of kitties in this level."))
    int32 Kitties = 0;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", BlueprintGetter=NumKittiesToPoop, meta=(DisplayName="Number of Kitties Yet to Poop", ToolTip="Number of kitties that have yet to poop."))
    int32 KittiesToPoop = 0;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", BlueprintGetter=GetLevelHealth, meta=(DisplayName="Level Health", ToolTip="The health of the current level.  Essentially, this acts as a surrogate for the player health, which does not exist."))
    float LevelHealth = KC::HEALTH::LEVEL_MAX;
    
//public:
    // in order to keep DamageLevelHealth() from needing to be declared public:
    //friend float ILevelHealthProxy::ForwardDamageToLevel(float, AController*);
    
private:
    void DamageLevelHealth(float damage);
};




inline UInventory* AKCPlayerState::GetInventory() const
{
    return Inventory;
}

inline int32 AKCPlayerState::NumKitties() const
{
    return Kitties;
}

inline int32 AKCPlayerState::NumKittiesToPoop() const
{
    return KittiesToPoop;
}

inline float AKCPlayerState::GetLevelHealth() const
{
    return LevelHealth;
}
