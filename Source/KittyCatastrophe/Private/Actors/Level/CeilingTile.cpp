// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/CeilingTile.h"
// Engine
#include "Components/ShapeComponent.h"
// KC
#include "Config/Constants/ObjectChannel.h"


ACeilingTile::ACeilingTile()
{
    namespace VISCHANNEL = KC::OBJECT_CHANNEL::VISIBILITY;
    
    checkf(OverlapBounds, TEXT("OverlapBounds is null."));
    checkf(Plane, TEXT("Plane is null."));
    
    OverlapBounds->AreaClass = nullptr;
    SetActorHiddenInGame( true );
    
    Plane->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    
    Plane->BodyInstance.SetResponseToAllChannels( ECR_Block );
    
    ECollisionChannel ignoreChannels[] =
    {
        ECollisionChannel::ECC_Visibility,
        ECollisionChannel::ECC_Camera,
        VISCHANNEL::KITTY_LOS
    };
    
    for (ECollisionChannel const& channel : ignoreChannels)
    {
        Plane->BodyInstance.SetResponseToChannel( channel, ECR_Ignore );
    }
}

void ACeilingTile::Init( float const height )
{
    FVector  location = {   0.0f, 0.0f, height };
    FRotator rotation = { 180.0f, 0.0f, 0.0f };
    
    SetActorRelativeLocation( location );
    SetActorRelativeRotation( rotation );
}
