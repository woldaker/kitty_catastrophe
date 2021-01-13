// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Enums/ECardinal.h"
#include "Utils/Log.h"


bool Cardinal::IsValid( ECardinal const direction )
{
    uint8 const directionValue = static_cast<uint8>(direction);
    
    return (directionValue >= Cardinal::DIRECTION_VALUE_MIN) &&
           (directionValue <= Cardinal::DIRECTION_VALUE_MAX);
}


ECardinal Cardinal::GetDirectionTurned( ECardinal const direction, int32 const num90DegTurns )
{
    if (!Cardinal::IsValid( direction ))
    {
        Log::Info( "Direction given not valid." );
        return direction;
    }
    
    if (num90DegTurns == 0) { return direction; }
    
    uint8 directionValue = static_cast<uint8>(direction) +
        (num90DegTurns % NUM_DIRECTION_VALUES);
    
    bool const valueTooLow  = (directionValue < DIRECTION_VALUE_MIN);
    bool const valueTooHigh = (directionValue > DIRECTION_VALUE_MAX);
    
    if (valueTooLow || valueTooHigh)
    {
        directionValue += ((valueTooLow ? +1 : -1) * NUM_DIRECTION_VALUES);
    }
    
    return static_cast<ECardinal>(directionValue);
}
