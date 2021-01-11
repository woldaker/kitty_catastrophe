// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Containers/EnumAsByte.h"
#include "Engine/EngineTypes.h"


namespace KC {
namespace /*KC::*/ OBJECT_CHANNEL {

namespace /*KC::OBJECT_CHANNEL::*/ COLLISION {
TEnumAsByte<ECollisionChannel> const KITTY          = ECollisionChannel::ECC_GameTraceChannel1;
TEnumAsByte<ECollisionChannel> const DAMAGE_CARRIER = ECollisionChannel::ECC_GameTraceChannel2;
} //ns KC::OBJECT_CHANNEL::COLLISION

namespace /*KC::OBJECT_CHANNEL::*/ VISIBILITY {
// "KITTY_LOS = Kitty Line-of-Sight"
TEnumAsByte<ECollisionChannel> const KITTY_LOS = ECollisionChannel::ECC_GameTraceChannel3;
} //ns KC::OBJECT_CHANNEL::VISIBILITY

} //ns KC::OBJECT_CHANNEL
} //ns KC
