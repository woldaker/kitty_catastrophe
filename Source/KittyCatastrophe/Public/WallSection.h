// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallSection.generated.h"

class USceneComponent;
class UStaticMeshComponent;


UCLASS(Abstract, Blueprintable, ClassGroup="Environment", meta=(ChildCannotTick, IsBlueprintBase="true", ToolTip="A resizeable section of wall."))
class KITTYCATASTROPHE_API AWallSection : public AActor
{
	GENERATED_BODY()
	
public:
	AWallSection();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ToolTip="Do not apply transforms to this component.  Use the root component instead."))
    UStaticMeshComponent* WallSection;
};
