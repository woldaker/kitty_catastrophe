// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "FloorSection.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Math/Vector.h"
//#include "NavAreas/NavArea_Default.h"
#include "UObject/ConstructorHelpers.h"

#include "MyDeveloperSettings.h"


AFloorSection::AFloorSection()
{
	PrimaryActorTick.bCanEverTick = false;
    SetActorTickEnabled(false);
    SetCanBeDamaged(false);

    FloorSection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSection"));
    PoopDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("PoopDetector"));

    RootComponent = FloorSection;
    PoopDetector->SetupAttachment(FloorSection);

    // FloorSection properties
    static ConstructorHelpers::FObjectFinder<UStaticMesh> plane_mesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
    if (plane_mesh.Succeeded()) {
        FloorSection->SetStaticMesh(plane_mesh.Object);
    }

    FloorSection->SetAutoActivate(true);
    FloorSection->SetCastShadow(false);
    FloorSection->SetGenerateOverlapEvents(false);
    FloorSection->SetMobility(EComponentMobility::Static);

    FloorSection->BodyInstance.bLockXRotation = true;
    FloorSection->BodyInstance.bLockYRotation = true;
    FloorSection->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
    FloorSection->BodyInstance.SetEnableGravity(false);

    // PoopDetector properties
    PoopDetector->bUseAttachParentBound = true;
    // TODO Set NavArea to either Default or None because it defaults to Obstacle
    //PoopDetector->SetAreaClass(UNavArea_Default::StaticClass());
    PoopDetector->SetAutoActivate(true);
    PoopDetector->SetCanEverAffectNavigation(false);
    PoopDetector->SetMobility(EComponentMobility::Static);
    PoopDetector->SetReceivesDecals(false);
    PoopDetector->SetRelativeScale3D(FVector(1.55f, 1.55f, 0.1f));

    PoopDetector->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PoopDetector->BodyInstance.SetEnableGravity(false);
    PoopDetector->BodyInstance.SetObjectType(ECC_WorldStatic);

    // Detect Poop and ignore everything else
    PoopDetector->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
    PoopDetector->BodyInstance.SetResponseToChannel(GetDefault<UMyDeveloperSettings>()->ECC_Poop, ECR_Overlap);
}

float AFloorSection::GetDamageMultiplier() const
{
    return DAMAGE_MULTIPLIER;
}
