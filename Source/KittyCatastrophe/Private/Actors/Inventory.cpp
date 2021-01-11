// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Inventory.h"
#include "Config/Constants/Inventory.h"
#include "Utils/Log.h"


UInventory::UInventory()
{
    for ( ELure lureType : TEnumRange<ELure>() )
    {
        LureTallies.Add( lureType, 0 );
    }
    
    LureTallies[ ELure::DEFAULT ] = KC::INVENTORY::INFINITE_SUPPLY;
}


void UInventory::AddLure( ELure const lureType, int32 const amount )
{
    FString const lureName = Lure::GetName( lureType );
    
    if (Lure::IsAbstract( lureType ))
    {
        Log::Warn( "Cannot add to inventory lures of type \"{0}\": type is abstract.", lureName );
        return;
    }

    if ( lureType == ELure::DEFAULT )
    {
        Log::Warn("Cannot add to inventory lures of default type \"{0}\".", lureName);
        return;
    }

    LureTallies[ lureType ] += amount;
    AvailableLureTypes.Add( lureType );
}


void UInventory::RemoveLure( ELure const lureType, int32 const amount )
{
    TCHAR const* lureName = Lure::GetName( lureType );
    
    if (Lure::IsAbstract( lureType ))
    {
        Log::Warn( "Cannot remove from inventory lures of type \"{0}\": type is abstract.", lureName );
        return;
    }

    if ( lureType == ELure::DEFAULT )
    {
        Log::Warn( "Cannot remove from inventory lures of default lure type \"{0}\".", lureName );
        return;
    }

    int32& lureCount = LureTallies[ lureType ];

    if (lureCount >= amount)
    {
        lureCount -= amount;
    }
    else
    {
        Log::Info(
            "Attempting to remove {0} lures of type {1} but only {2} in inventory.  All lures of that type were removed.",
            amount, lureName, lureCount
        );
        lureCount = 0;
    }

    if (lureCount == 0)
    {
        AvailableLureTypes.Remove( lureType );

        if (ActiveLureType == lureType)
        {
            ActiveLureType = ELure::DEFAULT;
        }
    }
}


void UInventory::SetActiveLureType( ELure const lureType )
{
    if (!AvailableLureTypes.Contains( lureType ))
    {
        Log::Warn(
            "Cannot set current lure to type {0}: no lures of that type in inventory.",
            Lure::GetName( lureType )
        );
        return;
    }
    
    ActiveLureType = lureType;
}
