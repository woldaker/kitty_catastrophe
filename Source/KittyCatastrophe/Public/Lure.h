// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
//#include "Components/TimelineComponent.h"
#include "Engine/DataTable.h"
//#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Templates/SubclassOf.h"
#include "MyDeveloperSettings.h"
#include "Lure.generated.h"

class UAIPerceptionStimuliSourceComponent;
//class UCurveFloat;
//class UMaterialInterface;
class UStaticMeshComponent;


UENUM(BlueprintType)
enum class ELureType : uint8
{
	// Lures
	Yarnball  = 0 UMETA(DisplayName="Yarnball"),
	RubberMouse   UMETA(DisplayName="Rubber Mouse"),
	KleenexBox    UMETA(DisplayName="Kleenex Box"),
	// Deterrents
	ToyRobot      UMETA(DisplayName="Toy Robot"),
	VacuumCleaner UMETA(DisplayName="Vacuum Cleaner"),

	Max UMETA(Hidden)
};

namespace ELureType_ {
ELureType const Default = ELureType::Yarnball;
FString GetName(ELureType const& lure_type);
}


USTRUCT(BlueprintType, meta=(DisplayName="Lure Class LUT"))
struct FLureClassLUT : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="Lure Blueprint Subclass"))
    TSubclassOf<ALure> BPClass;
};


UCLASS(Abstract, ClassGroup="Lures", meta=(DisplayName="Lure", IsBlueprintBase="true"))
class KITTYCATASTROPHE_API ALure : public AActor
{
	GENERATED_BODY()

public:
    ALure();

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="State", meta=(ClampMin=0, ClampMax=300, DisplayName="Time to Live", ToolTip="The number of seconds left before this lure is automatically destroyed.  Interactions with kitties will reset the timer.  Read-Only; modify LIFESPAN to indirectly affect this variable."))
    int32 TimeToLive = GetDefault<UMyDeveloperSettings>()->LureLifespan;

    //TODO make this static const?
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Constants", meta=(ClampMin=1, ClampMax=300, DisplayName="Lifespan", ToolTip="The number of seconds that this lure will be allowed to exist without being interacted with.  Interactions with kitties will reset the timer to this value."))
    int32 LIFESPAN = GetDefault<UMyDeveloperSettings>()->LureLifespan;

    //TODO make this static const?
    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Constants", meta=(ClampMin=1, ClampMax=10, DisplayName="Flicker Duration", ToolTip="The amount of time the flicker visibility effect lasts before automatic destruction."))
    //int32 FLICKER_DURATION = GetDefault<UMyDeveloperSettings>()->LureFlickerDuration;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Materials", meta=(DisplayName="Mesh Base Material", ToolTip="The base material from which the mesh's dynamic material instance will be created."))
    //UMaterialInterface* MeshBaseMaterial;


    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Called once per second from BeginPlay."))
    void DecrementTimeToLive();

    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Resets this lure's Time to Live, preventing it from being destroyed for that much longer."))
    void ResetTimeToLive();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Constants", meta=(ToolTip="The height, in world coordinates, necessary to drop this object and not be colliding with another instance of itself directly underneath it.  Usually a little more than twice the height of the mesh."))
    UPARAM(DisplayName="Drop Height") float GetDropHeight() const;

    UFUNCTION(BlueprintCallable, Category="State", meta=(ToolTip="Activates this lure's AI Perception Stimuli, making it visible to kitties."))
    void Activate();

    //UFUNCTION(BlueprintCallable, BlueprintPure, Category="Materials", meta=(DisplayName="Has Translucence", ToolTip="Returns true if the mesh's material (slot 0) uses the Masked Blend Mode."))
    //bool const HasTranslucence() const;

    //UFUNCTION(BlueprintCallable, Category="Materials", meta=(DisplayName="Set Opacity", ToolTip="Sets the Opacity parameter on the mesh's material (slot 0) to the provided value.  Does nothing if the material has no scalar parameter named \"Opacity\"."))
    //void SetOpacity(UPARAM(meta=(ClampMin=0.0f, ClampMax=1.0f)) float opacity);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear)
    UAIPerceptionStimuliSourceComponent* Stimuli;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Mesh;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(DisplayName="Flicker Timeline", ToolTip="Drives the flickering visibility of the mesh before it is destroyed."))
    //UTimelineComponent* FlickerTimeline;
    //FTimeline FlickerTimeline;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, NoClear, meta=(DisplayName="Flicker Curve"))
    //UCurveFloat* FlickerCurve;

    //FTimerHandle FlickerTimerHandle;

    // Event delegates
    //UPROPERTY(BlueprintReadOnly, meta=(DisplayName="Flicker Update Delegate"))
    //FOnTimelineFloat FlickerFloatEvent{};

    // Event functions
    //UFUNCTION()
    //void OnFlickerUpdate(float opacity);

//    UFUNCTION()
//	virtual void BeginPlay() override;

    UFUNCTION()
    virtual void PostActorCreated() override;

//public:
//	virtual void Tick(float DeltaTime) override;
};
