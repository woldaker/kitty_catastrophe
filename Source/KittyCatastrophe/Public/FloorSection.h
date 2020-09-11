// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSection.generated.h"

class UStaticMeshComponent;
class UBoxComponent;


UCLASS(Abstract, Blueprintable, ClassGroup="Environment", ShowFunctions=("Constants"), meta=(ChildCannotTick, IsBlueprintBase="true", ToolTip="A resizeable section of flooring."))
class KITTYCATASTROPHE_API AFloorSection : public AActor
{
	GENERATED_BODY()
	
public:
	AFloorSection();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Constants", meta=(DisplayName="Get Damage Multiplier", ToolTip="The damage multiplier for this floor type."))
    virtual UPARAM(DisplayName="Damage Multiplier") float GetDamageMultiplier() const final;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Floor Section", ToolTip="A resizeable section of flooring."))
    UStaticMeshComponent* FloorSection;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Poop Detector", ToolTip="Collider that overlaps with poop and ignores everything else."))
    UBoxComponent* PoopDetector;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintGetter="GetDamageMultiplier", Category="Constants", meta=(ClampMin=0.0f, DisplayName="Damage Multiplier"))
    float DAMAGE_MULTIPLIER = 1.0f;
};
