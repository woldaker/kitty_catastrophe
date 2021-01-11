// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "KCDeveloperSettings.generated.h"


UCLASS(BlueprintType, meta=(DisplayName="Kitty Catastrophe Settings"))
class KITTYCATASTROPHE_API UKCDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
// DEFAULT VALUES
/////////////////
    // Lure
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Lure", meta=(ClampMin=3, ClampMax=60, DisplayName="Lure Lifespan", ToolTip="The number of seconds a lure exists for, without being interacted with, before it disappears."))
    int32 LureLifespan = 30;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Lure", meta=(ClampMin=0, ClampMax=10, DisplayName="Lure Flicker Duration", ToolTip="The number of seconds of a lure's lifespan during which it will flicker before disappearing.  If greater than its lifespan, this value will be clamped to equal it."))
    int32 LureFlickerDuration = 5;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Lure", meta=(DisplayName="Lure Drop Height", ToolTip="The height above the floor on the Z-axis in which lures are dropped into the scene."))
    float LureDropHeight = 200.0f;

    // Camera
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Camera", meta=(DisplayName="Camera Orthogonal Width", ToolTip="The width of floorspace that the camera can see, in world coordinate units."))
    float CameraOrthoWidth = 6000.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Camera", meta=(DisplayName="Camera Location", ToolTip="Location of the main view camera."))
    FVector CameraLocation = FVector{0.0f, 2000.0f, 2000.0f};

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default Values|Camera", meta=(DisplayName="Camera Rotation", ToolTip="Rotation of the main view camera."))
    FRotator CameraRotation = FRotator{-45.0f, -90.0f, 0.0f};
    
// LEVELMAPS
////////////
    // Encoding
    /*
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level Maps|Encoding", meta=(DisplayName="Empty/None", ToolTip="An empty space.  Used for any context."))
    TCHAR MapCharEmpty = ' ';
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level Maps|Encoding", meta=(DisplayName="Carpet"))
    TCHAR MapCharCarpet = 'c';
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level Maps|Encoding", meta=(DisplayName="Hardwood"))
    TCHAR MapCharHardwood = 'h';
    */
};
