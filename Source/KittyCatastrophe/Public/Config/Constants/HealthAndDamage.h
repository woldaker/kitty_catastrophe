// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once


namespace KC {
namespace HEALTH {

constexpr float LEVEL_MAX = 1000.0f;
constexpr float PROXYACTOR_MAX = LEVEL_MAX / 10;

} //ns KC::HEALTH

namespace //KC::
    DAMAGE {
constexpr float CARRIER_POOL_MAX = HEALTH::LEVEL_MAX / 10;
constexpr float CARRIER_SCALING_POOL_INITIAL = CARRIER_POOL_MAX * 0.3f;

} //ns KC::DAMAGE
} //ns KC
