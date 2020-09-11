// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Containers/EnumAsByte.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/EngineTypes.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "MyDeveloperSettings.generated.h"


// INPUTS
#define INPUT_ACTION_MAPPING_TOUCH_1 "Finger1"

// PATHS
#define PATH_DATA_TABLE_LURE_CLASSES     "DataTable'/Game/KittyCatastrophe/Core/Engine/DT_LureClasses.DT_LureClasses'"
#define PATH_FLICKER_CURVE               "FloatCurve'/Game/KittyCatastrophe/Core/Engine/Curve_Flicker_Float.Curve_Flicker_Float'"
#define PATH_STATIC_MESH_TROUGH          "StaticMesh'/Game/KittyCatastrophe/Core/Interactables/SM_Trough.SM_Trough'"
#define PATH_STATIC_MESH_TROUGH_CONTENTS "StaticMesh'/Game/KittyCatastrophe/Core/Interactables/SM_TroughContents.SM_TroughContents'"

UCLASS(BlueprintType, meta=(DisplayName="My Developer Settings"))
class KITTYCATASTROPHE_API UMyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
    // Collision channels
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Collision Channels|Object")
    TEnumAsByte<ECollisionChannel> ECC_Kitty = ECollisionChannel::ECC_GameTraceChannel1;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Collision Channels|Object")
    TEnumAsByte<ECollisionChannel> ECC_Poop = ECollisionChannel::ECC_GameTraceChannel2;

    // Visibility channels
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Collision Channels|Trace")
    TEnumAsByte<ECollisionChannel> ECC_KittyLOS = ECollisionChannel::ECC_GameTraceChannel3;

    // Default Values
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Lure")
    int32 LureLifespan = 30;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Lure")
    int32 LureFlickerDuration = 5;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Lure")
    float LureDropHeightMultiplier = 2.5f;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Camera")
    float CameraOrthoWidth = 6000.0f;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Camera")
    FVector CameraLocation = FVector(0.0f, 2000.0f, 2000.0f);

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default Values|Camera")
    FRotator CameraRotation = FRotator(-45.0f, -90.0f, 0.0f);
};
