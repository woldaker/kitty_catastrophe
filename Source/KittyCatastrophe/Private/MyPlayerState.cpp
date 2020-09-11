// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "MyPlayerState.h"
#include "Inventory.h"
#include "Utils/Log.h"

AMyPlayerState::AMyPlayerState()
{
    Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}


UInventory* AMyPlayerState::GetInventory()
{
    if (!Inventory)
    {
        Log::Warn("Cannot complete call to GetInventory(); inventory is null.");
        return nullptr;
    }
    return Inventory;
}
