// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "WallSection.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Math/Rotator.h"
#include "UObject/ConstructorHelpers.h"

AWallSection::AWallSection()
{
	PrimaryActorTick.bCanEverTick = false;
    SetActorTickEnabled(false);
    SetCanBeDamaged(false);

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    WallSection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallSection"));

    RootComponent = Root;
    WallSection->SetupAttachment(Root);

    // Root properties
    Root->SetAutoActivate(true);
    Root->SetMobility(EComponentMobility::Static);

    // Wall properties
    static ConstructorHelpers::FObjectFinder<UStaticMesh> plane_mesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
    if (plane_mesh.Succeeded()) {
        WallSection->SetStaticMesh(plane_mesh.Object);
    }

    // Walls should already be vertical when initialized
    WallSection->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

    WallSection->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    WallSection->SetAutoActivate(true);
    WallSection->SetCanEverAffectNavigation(false);
    WallSection->SetGenerateOverlapEvents(false);
    WallSection->SetMobility(EComponentMobility::Static);
    WallSection->SetUseCCD(true);

    WallSection->BodyInstance.bLockXRotation = true;
    WallSection->BodyInstance.bLockYRotation = true;
    WallSection->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
    WallSection->BodyInstance.SetEnableGravity(false);
}
