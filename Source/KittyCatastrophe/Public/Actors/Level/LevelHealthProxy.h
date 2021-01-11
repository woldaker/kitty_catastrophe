// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "UObject/Interface.h"
// KC
#include "Config/Constants/HealthAndDamage.h"
#include "LevelHealthProxy.generated.h"


UINTERFACE(Blueprintable, BlueprintType, Category="Map", meta=(DisplayName="Level Health Proxy", ToolTip="Any changes to the Health property of an actor which implements this interface will propagate those changes to the PlayerState's LevelHealth."))
class KITTYCATASTROPHE_API ULevelHealthProxy : public UInterface { GENERATED_BODY() };
class KITTYCATASTROPHE_API ILevelHealthProxy
{
    GENERATED_BODY()
protected:
    float Health = KC::HEALTH::PROXYACTOR_MAX;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ILevelHealthProxy", meta=(DisplayName="Get Max Health", ToolTip="Override this function and simply have it return the corresponding value for the subclass's particular type."))
    UPARAM(DisplayName="Max Health")
    float GetMaxHealth() const;
    float GetMaxHealth_Implementation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ILevelHealthProxy", meta=(DisplayName="Get Multiplier", ToolTip="Override this function and simply have it return the corresponding value for the subclass's particular type."))
    UPARAM(DisplayName="Multiplier")
    float GetMultiplier() const;
    float GetMultiplier_Implementation() const;
    
    virtual float CalculateLevelDamage( float const damage ) const;

    // Returns the amount of damage actually dealt (to this, not to the level)
    virtual float ForwardDamageToLevel( float const damage, AController* instigator ) final;
};


// INLINE DEFINITIONS
/////////////////////
inline float ILevelHealthProxy::GetMaxHealth_Implementation() const
{
    return KC::HEALTH::PROXYACTOR_MAX;
}


inline float ILevelHealthProxy::GetMultiplier_Implementation() const
{
   return 1.0f;
}


inline float ILevelHealthProxy::CalculateLevelDamage(float const damage) const
{
    return (damage * GetMultiplier());
}
