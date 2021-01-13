// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Core/KCPlayerState.h"

#include "Actors/Inventory.h"
#include "Utils/Log.h"


AKCPlayerState::AKCPlayerState()
{
    Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
    checkf(Inventory, TEXT("error constructing Inventory."));
}


void AKCPlayerState::DamageLevelHealth(float damage)
{
    float const originalLevelHealth = LevelHealth;
    LevelHealth = FMath::Clamp(LevelHealth - damage, 0.0f, KC::HEALTH::LEVEL_MAX);
    
    if ((originalLevelHealth > 0.0f) && (LevelHealth <= 0.0f))
    {
        Log::Info("CATASTROPHE!!!");
        
    }
}
