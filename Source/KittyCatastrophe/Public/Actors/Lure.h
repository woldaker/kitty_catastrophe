// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Data/LUTEntry_BPClass_Lure.h"
#include "Enums/ELure.h"

#include "Lure.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UStaticMeshComponent;


UCLASS(Abstract, Blueprintable, ClassGroup="Lures", meta=(DisplayName="Lure", IsBlueprintBase="true"))
class KITTYCATASTROPHE_API ALure : public AActor
{
	GENERATED_BODY()
public:
    ALure();

    // CONSTANTS & READ-ONLY properties
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="State", meta=(ClampMin=0, ClampMax=300, DisplayName="Time to Live", ToolTip="The number of seconds left before this lure is automatically destroyed.  Interactions with kitties will reset the timer.  Read-Only; modify LIFESPAN to indirectly affect this variable."))
    int32 TTL;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Constants", meta=(ClampMin=1, ClampMax=300, DisplayName="Lifespan", ToolTip="The number of seconds that this lure will be allowed to exist without being interacted with.  Interactions with kitties will reset the timer to this value."))
    int32 LIFESPAN;

    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Called once per second from BeginPlay."))
    void DecrementTTL();

    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Resets this lure's Time to Live, preventing it from being destroyed for that much longer."))
    void ResetTTL();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Constants", meta=(ToolTip="The height, in world coordinates, necessary to drop this object and not be colliding with another instance of itself directly underneath it.  Usually a little more than twice the height of the mesh."))
    UPARAM(DisplayName="Drop Height") float GetDropHeight() const;

    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Activates this lure's AI Perception Stimuli, making it visible to kitties."))
    void Activate();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear)
    UAIPerceptionStimuliSourceComponent* Stimuli = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Mesh = nullptr;

    UFUNCTION()
    virtual void PostActorCreated() override;
};
