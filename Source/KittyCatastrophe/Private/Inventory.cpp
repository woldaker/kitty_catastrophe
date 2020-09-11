// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Inventory.h"
#include "Utils/Log.h"

UInventory::UInventory()
{
    ActiveLureType     =   ELureType_::Default;
    AvailableLureTypes = { ELureType_::Default };

    for (ELureType lure_type = static_cast<ELureType>(0); lure_type < ELureType::Max; lure_type = static_cast<ELureType>(static_cast<uint8>(lure_type) + 1))
    {
        LureCountTable.Add(lure_type);
    }

    LureCountTable[ELureType_::Default] = UInventory::INFINITE_SUPPLY;
}


void UInventory::AddLure(ELureType const& lure_type, int32 const amount)
{
    if (lure_type == ELureType_::Default)
    {
        Log::Info("Cannot add lures of default lure type.");
        return;
    }

    LureCountTable[lure_type] += amount;
    AvailableLureTypes.Add(lure_type);
}


void UInventory::RemoveLure(ELureType const& lure_type, int32 const amount)
{
    if (lure_type == ELureType_::Default)
    {
        Log::Info("Cannot remove lures of default lure type.");
        return;
    }

    int32& LureCount = LureCountTable[lure_type];

    if (LureCount >= amount)
    {
        LureCount -= amount;
    }
    else
    {
        Log::Warn("Attempting to remove {0} lures of type {1} but only {2} in inventory", amount, *ELureType_::GetName(lure_type), LureCount);
        LureCount = 0;
    }

    if (LureCount == 0)
    {
        AvailableLureTypes.Remove(lure_type);

        if (ActiveLureType == lure_type)
        {
            ActiveLureType = ELureType_::Default;
        }
    }
}


ELureType UInventory::GetActiveLureType() const
{
    return ActiveLureType;
}


void UInventory::SetActiveLureType(ELureType const& lure_type)
{
    if (AvailableLureTypes.Contains(lure_type))
    {
        ActiveLureType = lure_type;
    }
    else
    {
        Log::Warn("Cannot set current lure to type {0}: no lures of that type in inventory.", *ELureType_::GetName(lure_type));
    }
}


TSet<ELureType> const& UInventory::GetAvailableLureTypes() const
{
    return AvailableLureTypes;
}
