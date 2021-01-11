// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/WallTile.h"
// KC
#include "Config/Constants/Level.h"
//#include "Config/Constants/Log.h"


AWallTile::AWallTile()
{
    checkf( Plane, TEXT(/*KCINFO*/ "Plane is null.") );
    
    Plane->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    Plane->SetCastShadow(true);
}


void AWallTile::Orient( ECardinal const direction )
{
    namespace WALL = KC::LEVEL::MAP::TILE::WALL;
    
    FVector location = (AMapTile::UnitExtent * Cardinal::GetUnitVector( direction ));
    location.Z += (WALL::HEIGHT_SCALE * AMapTile::UnitExtent);
    
    FRotator rotation = Cardinal::GetRotator(
        Cardinal::GetDirectionOpposite( direction )
    );
    
    FVector scale = { WALL::HEIGHT_SCALE, 1.0f, 1.0f };
    
    SetActorRelativeTransform(
        { rotation, location, scale },
        false,
        nullptr,
        ETeleportType::None
    );
}
