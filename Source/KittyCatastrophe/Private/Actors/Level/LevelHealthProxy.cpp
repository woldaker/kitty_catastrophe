// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Level/LevelHealthProxy.h"
// KC
#include "Core/KCPlayerController.h"
#include "Core/KCPlayerState.h"


float ILevelHealthProxy::ForwardDamageToLevel( float const damage, AController* instigator )
{
    AKCPlayerController* player = Cast<AKCPlayerController>( instigator );
    checkf( player, TEXT("Can't get player controller.") );
    
    AKCPlayerState* playerState = player->GetPlayerState<AKCPlayerState>();
    checkf( playerState, TEXT("Can't get player state.") );
    
    float const originalHealth = Health;
    Health = FMath::Clamp( (Health - damage), 0.0f, GetMaxHealth() );
    
    // damageDealt may be different than damage
    float damageDealt = originalHealth - Health;
    float levelDamageDealt = CalculateLevelDamage( damageDealt );
    
    playerState->DamageLevelHealth( levelDamageDealt );
    
    return damageDealt;
}
