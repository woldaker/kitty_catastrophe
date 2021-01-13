// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "Logging/LogVerbosity.h"
#include "Math/Color.h"
// KC
//#define KCLOG_STRINGIFY(x) #x
//#define KCLOG_TOSTRING(x) KCLOG_STRINGIFY(x)
//#define KCINFO __FILE__ "(" KCLOG_TOSTRING(__LINE__) ") :"


namespace KC {
namespace /*KC::*/ LOG {

namespace /*KC::LOG::*/ DEBUG {
FColor const COLOR = FColor::Emerald;
constexpr float DURATION = 1.5f;
} //ns KC::LOG::DEBUG

namespace /*KC::LOG::*/ INFO {
FColor const COLOR = FColor::Yellow;
constexpr float DURATION = 2.5f;
} //ns KC::LOG::INFO

namespace /*KC::LOG::*/ WARN {
FColor const COLOR = FColor::Orange;
constexpr float DURATION = 4.0f;
} //ns KC::LOG::WARN

namespace /*KC::LOG::*/ ERROR {
FColor const COLOR = FColor::Red;
constexpr float DURATION = 8.0f;
} //ns KC::LOG::ERROR

namespace /*KC::LOG::*/ FATAL {
FColor const COLOR = FColor::Magenta;
constexpr float DURATION = 10.0f;
} //ns KC::LOG::FATAL

} //ns KC::LOG
} //ns KC
