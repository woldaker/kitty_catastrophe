// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Lure.h"
#include "Components/StaticMeshComponent.h"
//#include "Curves/CurveFloat.h"
//#include "Materials/MaterialInstanceDynamic.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
//#include "UObject/ConstructorHelpers.h"

FString ELureType_::GetName(ELureType const& lure_type)
{
    switch(lure_type)
    {
        case ELureType::Yarnball:
            return TEXT("Yarnball");
        default:
            break;
    }

    return TEXT("");
}


ALure::ALure()
{
	PrimaryActorTick.bCanEverTick = true;

    SetCanBeDamaged(false);
    bRelevantForLevelBounds = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    checkf(Mesh, TEXT("ALure::Mesh instantiated to null"))
    RootComponent = Mesh;

    Stimuli = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli"));
    checkf(Stimuli, TEXT("ALure::Stimuli instantiated to null"))
    //FlickerTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Flicker Timeline"));
    //checkf(FlickerTimeline, TEXT("ALure::FlickerTimeline instantiated to null"));

    // Mesh properties
    Mesh->SetCanEverAffectNavigation(false);
    Mesh->SetGenerateOverlapEvents(false);
    Mesh->SetMobility(EComponentMobility::Movable);
    Mesh->SetReceivesDecals(false);
    Mesh->SetSimulatePhysics(false);

    Mesh->BodyInstance.SetEnableGravity(false);
    Mesh->BodyInstance.SetObjectType(ECC_PhysicsBody);
    Mesh->BodyInstance.SetUseCCD(true);

    Mesh->BodyInstance.SetResponseToAllChannels(ECR_Block);
    Mesh->BodyInstance.SetResponseToChannel(ECC_Visibility, ECR_Ignore);
    Mesh->BodyInstance.SetResponseToChannel(GetDefault<UMyDeveloperSettings>()->ECC_KittyLOS, ECR_Ignore);
    Mesh->BodyInstance.SetResponseToChannel(GetDefault<UMyDeveloperSettings>()->ECC_Poop, ECR_Overlap);

    // Create the float curve for the timeline
    /*
    static ConstructorHelpers::FObjectFinder<UCurveFloat> float_curve(TEXT(PATH_FLICKER_CURVE));
    if (float_curve.Succeeded())
    {
        FlickerCurve = float_curve.Object;
    }
    else
    {
        FlickerCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("Flicker Curve"));
        UE_LOG(LogTemp, Warning, TEXT("Couldn't set float curve for timeline in ALure constructor"));
    }
    */

    // Bind event delegates
    //FlickerFloatEvent.BindUFunction(this, FName(TEXT("OnFlickerUpdate")));
    //FlickerTimeline.AddInterpFloat(FlickerCurve, FlickerFloatEvent, FName(TEXT("Flicker")));

    //FlickerFloatEvent.BindDynamic(this, &ALure::OnFlickerUpdate);
}

/*
void ALure::OnFlickerUpdate(float opacity)
{
    if (HasTranslucence())
    {
        SetOpacity(opacity);
    }
    else
    {
        RootComponent->SetVisibility(FMath::RoundHalfFromZero(opacity) != 0.0f);
    }
}
*/


void ALure::DecrementTimeToLive()
{
    TimeToLive--;

    if (TimeToLive <= 0)
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


void ALure::ResetTimeToLive()
{
    //FlickerTimeline.Stop();
    TimeToLive = LIFESPAN;
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
    FVector origin;
    FVector bounding_box;

    GetActorBounds(false, origin, bounding_box, true);

    return GetDefault<UMyDeveloperSettings>()->LureDropHeightMultiplier * bounding_box.GetAbsMax() * 2;
}


void ALure::Activate()
{
    Stimuli->RegisterWithPerceptionSystem();
    ResetTimeToLive();
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
    Stimuli->RegisterForSense(TSubclassOf<UAISense_Sight>());

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
