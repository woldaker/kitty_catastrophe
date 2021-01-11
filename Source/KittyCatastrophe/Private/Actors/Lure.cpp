// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Lure.h"
// Engine
#include "Components/StaticMeshComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
// KC
//#include "Config/Constants/Log.h"
#include "Config/Constants/ObjectChannel.h"
#include "Config/KCDeveloperSettings.h"


ALure::ALure() :
    TTL( GetDefault<UKCDeveloperSettings>()->LureLifespan ),
    LIFESPAN( GetDefault<UKCDeveloperSettings>()->LureLifespan )
{
    using AIStimulus = UAIPerceptionStimuliSourceComponent;
    
	PrimaryActorTick.bCanEverTick = true;

    SetCanBeDamaged( false );
    bRelevantForLevelBounds = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Mesh") );
    checkf(Mesh, TEXT(/*KCINFO*/ "Mesh instantiated to null"))
    RootComponent = Mesh;

    Stimuli = CreateDefaultSubobject<AIStimulus>( TEXT("Stimuli") );
    checkf(Stimuli, TEXT(/*KCINFO*/ "Stimuli instantiated to null"))

    // Mesh properties
    Mesh->SetCanEverAffectNavigation( false );
    Mesh->SetGenerateOverlapEvents( false );
    Mesh->SetMobility( EComponentMobility::Movable );
    Mesh->SetReceivesDecals( false );
    Mesh->SetSimulatePhysics( false );

    Mesh->BodyInstance.SetEnableGravity( false );
    Mesh->BodyInstance.SetObjectType( ECC_PhysicsBody );
    Mesh->BodyInstance.SetUseCCD( true );

    Mesh->BodyInstance.SetResponseToAllChannels( ECR_Block );
    Mesh->BodyInstance.SetResponseToChannel( ECC_Visibility, ECR_Ignore );
    Mesh->BodyInstance.SetResponseToChannel(
        KC::OBJECT_CHANNEL::COLLISION::DAMAGE_CARRIER,
        ECR_Overlap
    );
    Mesh->BodyInstance.SetResponseToChannel(
        KC::OBJECT_CHANNEL::VISIBILITY::KITTY_LOS,
        ECR_Ignore
    );
}


void ALure::DecrementTTL()
{
    TTL--;

    if (TTL <= 0)
    {
        //RootComponent->SetVisibility(false);
        //GetWorldTimerManager().ClearTimer(FlickerTimerHandle);
        //FlickerTimeline.Stop();
        Destroy();
    }
    /*
    else if (TimeToLive == FLICKER_DURATION)
    {
        //TODO Call material function Flicker()
        //FlickerTimeline.PlayFromStart();
    }
    */
}


void ALure::ResetTTL()
{
    //FlickerTimeline.Stop();
    TTL = LIFESPAN;
    /*
    if (HasTranslucence())
    {
        SetOpacity(1.0f);
    }
    else
    {
       //TODO Set material Opacity to 1
    }
    */
}


float ALure::GetDropHeight() const
{
    UKCDeveloperSettings const* CFG = GetDefault<UKCDeveloperSettings>();

    FVector origin;
    FVector boundingBox;

    GetActorBounds(false, origin, boundingBox, true);

    return CFG->LureDropHeight * boundingBox.GetAbsMax() * 2;
}


void ALure::Activate()
{
    Stimuli->RegisterWithPerceptionSystem();
    ResetTTL();
    Mesh->SetSimulatePhysics(true);
    Mesh->BodyInstance.SetEnableGravity(true);
}

/*
bool const ALure::HasTranslucence() const
{
    return Mesh->GetMaterial(0)->GetBlendMode() == EBlendMode::BLEND_Masked;
}
*/

/*
void ALure::SetOpacity(float opacity)
{
    if (auto* mid = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(0)))
    {
        mid->SetScalarParameterValue(TEXT("Opacity"), opacity);
    }
}
*/

/*
void ALure::BeginPlay()
{
	Super::BeginPlay();

    if (HasTranslucence())
    {
        SetOpacity(1.0f);
    }

    // Start the TimeToLive timer, repeat every 1 second
    //GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &ALure::DecrementTimeToLive, 1.0f, true);
}
*/


void ALure::PostActorCreated()
{
    /*
    if (MeshBaseMaterial)
    {
        UMaterialInstanceDynamic* dynamic_material = UMaterialInstanceDynamic::Create(MeshBaseMaterial, this);
        if (dynamic_material)
        {
            Mesh->SetMaterial(0, dynamic_material);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Could not create dynamic material for lure's StaticMeshComponent: error during creation."))
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not create dynamic material for lure's StaticMeshComponent: no base material set."))
    }
    */

    // Register as stimuli only after drop action is completed (i.e. finger is lifted)
    Stimuli->UnregisterFromPerceptionSystem();
    
    // Stimuli properties
    Stimuli->RegisterForSense( TSubclassOf<UAISense_Sight>() );

    // This has to be done here and not in construction because only here are we guaranteed that the child BP class
    //   has set up its material completely.
    /*
    if (HasTranslucence())
    {
        SetOpacity(0.5f);
    }
    */
}

/*
void ALure::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FlickerTimeline.IsPlaying())
    {
        FlickerTimeline.TickTimeline(DeltaTime);
    }
}
*/
