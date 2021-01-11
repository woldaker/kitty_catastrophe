// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// KC
#include "Actors/Level/LevelHealthProxy.h"
#include "DamageReceiver.generated.h"

class UShapeComponent;


UCLASS(Abstract, Blueprintable, BlueprintType, Category="Map", ClassGroup=(Map,HealthProxy), meta=(IsBlueprintBase="true", DisplayName="Damage Receiver Component", ToolTip="Base class for any actor that can forward damage/healing done to the level's health instead of itself."))
class KITTYCATASTROPHE_API ADamageReceiver : public AActor, public ILevelHealthProxy
{
    GENERATED_BODY()
public:
    virtual float TakeDamage(
        float               damageAmount,
        FDamageEvent const& damageEvent,
        AController*        eventInstigator,
        AActor*             damageCauser
    );
    
    friend bool operator< ( ADamageReceiver const& left, ADamageReceiver const& right );
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, meta=(DisplayName="Overlap Bounds", ToolTip="Shape used by DamageCarrier actors which hit multiple DamageReceiver actors simultaneously, to gather information about the ones it hit."))
    UShapeComponent* OverlapBounds = nullptr;
    
    // The bounds arg should be created and have its extent and scale set before calling,
    //   and keep in mind that this function will be called from within a constructor body.
    virtual void InitOverlapBounds();
};


// INLINE DEFINITIONS
/////////////////////
inline bool operator< ( ADamageReceiver const& left, ADamageReceiver const& right )
{
    return left.GetMultiplier() < right.GetMultiplier();
}
