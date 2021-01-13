// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/MapTile.h"
// Engine
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
// KC
#include "Config/Constants/Level.h"
#include "Config/Constants/Path.h"
#include "Utils/Log.h"

float AMapTile::UnitExtent = KC::LEVEL::MAP::TILE::UNIT_EXTENT_UNDEFINED;


AMapTile::AMapTile()
{
    namespace SM = KC::PATH::ASSET::STATIC_MESH;
    
    // OVERLAP BOUNDS
    // OverlapBounds is inherited from ADamageReceiver, but must be constructed here
    //   because ADamageReceiver doesn't yet know which UShapeComponent to make.
    OverlapBounds = CreateDefaultSubobject<UBoxComponent>( TEXT("Overlap Bounds") );
    checkf( OverlapBounds, TEXT("OverlapBounds is null.") );
    
    // PLANE MESH
    Plane = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Plane") );
    checkf( Plane, TEXT("Plane mesh component is null.") );
    
    //UStaticMesh* planeMesh = Cast<UStaticMesh>(
    //    FSoftObjectPath( *SM::ENGINE::BASIC_PLANE ).TryLoad()
    //);
    //checkf( planeMesh, TEXT("Couldn't create basic plane mesh.") );
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> planeMesh (
        *SM::ENGINE::BASIC_PLANE
    );
    checkf(
        planeMesh.Succeeded(),
        TEXT("Couldn't find basic plane mesh at location '%s'."),
        *SM::ENGINE::BASIC_PLANE
    );
    
    Plane->SetStaticMesh( planeMesh.Object );
    
    Plane->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;
    Plane->SetAutoActivate( true );
    Plane->SetCanEverAffectNavigation( false );
    Plane->SetCastShadow( false );
    Plane->SetGenerateOverlapEvents( false );
    Plane->SetMobility( EComponentMobility::Movable );
    Plane->SetNotifyRigidBodyCollision( true );
    Plane->SetReceivesDecals( true );
    Plane->SetSimulatePhysics( false );
    Plane->SetUseCCD( true );

    //Plane->BodyInstance.bLockXRotation    = true;
    //Plane->BodyInstance.bLockXTranslation = true;
    //Plane->BodyInstance.bLockYRotation    = true;
    //Plane->BodyInstance.bLockYTranslation = true;
    //Plane->BodyInstance.bLockZRotation    = true;
    //Plane->BodyInstance.bLockZTranslation = true;

    Plane->BodyInstance.SetCollisionProfileName( TEXT("BlockAll") );
    Plane->BodyInstance.SetEnableGravity( false );
    
    if (!AMapTile::IsUnitExtentSet())
    {
        // Set OverlapBounds using size of Plane mesh
        FVector const planeExtent = Plane->GetStaticMesh()->GetBoundingBox().GetExtent();
        
        if (planeExtent.X != planeExtent.Y)
        {
            Log::Warn( "Basic plane extents are not the same in the X and Y axes." );
        }
        
        AMapTile::UnitExtent = FMath::Max( planeExtent.X, planeExtent.Y );
    }
    
    InitOverlapBounds();
    
    Plane->SetupAttachment( OverlapBounds );
}


void AMapTile::InitOverlapBounds()
{
    namespace BOUNDS = KC::LEVEL::MAP::TILE::BOUNDS;
    
    checkf(
        AMapTile::IsUnitExtentSet(),
        TEXT("MapTile's unit extent must be set before calling this function.")
    );
    
    FVector const overlapExtent =
    {
        AMapTile::UnitExtent,
        AMapTile::UnitExtent,
        (AMapTile::UnitExtent * BOUNDS::NORMAL_TO_PLANE_LENGTH_RATIO)
    };
    
    Cast<UBoxComponent>( OverlapBounds )->InitBoxExtent( overlapExtent );

    Super::InitOverlapBounds();
    
    OverlapBounds->AreaClass = FNavigationSystem::GetDefaultWalkableArea();
    OverlapBounds->SetCanEverAffectNavigation( false );
}
