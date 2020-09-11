// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Math/Color.h"


namespace Constants
{

namespace Log
{
namespace Info
{
static const FColor MSG_COLOR = FColor::Turquoise;
static constexpr float MSG_DURATION = 2.0f;
} // END Log::Info

namespace Warn
{
static const FColor MSG_COLOR = FColor::Yellow;
static constexpr float MSG_DURATION = 5.0f;
} // END Log::Warn

namespace Error
{
static const FColor MSG_COLOR = FColor::Red;
static constexpr float MSG_DURATION = 10.0f;
} // END Log::Error
} // END Log

} // END Constants
