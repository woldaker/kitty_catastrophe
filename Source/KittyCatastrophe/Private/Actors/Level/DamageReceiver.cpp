// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/DamageReceiver.h"
// Engine
#include "Components/ShapeComponent.h"
// KC
#include "Config/Constants/Level.h"
#include "Config/Constants/ObjectChannel.h"


void ADamageReceiver::InitOverlapBounds()
{
    namespace COLLISION_CHANNEL = KC::OBJECT_CHANNEL::COLLISION;
    checkf(
        OverlapBounds,
        TEXT("OverlapBounds must be constructed before calling this method.")
    );
    
    OverlapBounds->bDrawOnlyIfSelected = true;
    
    OverlapBounds->SetAutoActivate( true );
    // OverlapBounds does NOT need to generate overlap events.
    //   It only needs to be able to be queried for overlaps.
    //   These are two different things.
    OverlapBounds->SetGenerateOverlapEvents( false );
    OverlapBounds->SetMobility( EComponentMobility::Movable );
    OverlapBounds->SetReceivesDecals( false );
    
    OverlapBounds->BodyInstance.SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    OverlapBounds->BodyInstance.SetEnableGravity( false );
    //TODO: SetObjectType( DamageReceiver ); <-- create and use custom object channel?
    OverlapBounds->BodyInstance.SetObjectType( ECC_WorldStatic );
    
    //TODO: do this in child class (or even at all?):
    //OverlapBounds->BodyInstance.bLockXRotation = true;
    //OverlapBounds->BodyInstance.bLockYRotation = true;
    
    // Detect damage carriers and ignore everything else
    OverlapBounds->BodyInstance.SetResponseToAllChannels( ECR_Ignore );
    OverlapBounds->BodyInstance.SetResponseToChannel(
        COLLISION_CHANNEL::DAMAGE_CARRIER,
        ECR_Overlap
    );
    
    if (!RootComponent)
    {
        RootComponent = OverlapBounds;
    }
}


float ADamageReceiver::TakeDamage(
    float               damageAmount,
    FDamageEvent const& damageEvent,
    AController*        eventInstigator,
    AActor*             damageCauser
) {
    // TODO: Is this call necessary?  Possibly redundant; maybe even incorrect.
    Super::TakeDamage( damageAmount, damageEvent, eventInstigator, damageCauser );
    
    return ForwardDamageToLevel( damageAmount, eventInstigator );
}
