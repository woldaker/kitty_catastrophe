// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "Engine/Engine.h"
//#include "Containers/Array.h"
#include "Containers/UnrealString.h"
#include "HAL/Platform.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Math/Color.h"
#include "Misc/CoreMiscDefines.h"
#include "Templates/UnrealTemplate.h"
// KC
#include "Config/Constants/Log.h"
#include "KittyCatastrophe/KittyCatastrophe.h"


namespace Log {
namespace Private {
static void LogToScreen( float const duration, FColor const color, FString const& message )
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage( INDEX_NONE, duration, color, message );
    }

    UE_LOG(KCLog, Display, TEXT("%s"), *message);
}

// base case
inline static FString const& FormatString( FString const& message )
{
    return message;
}

// recursive case
template <typename... Args>
static FString const FormatString( FString const& message, Args&&... args )
{
    return FString::Format( *message, {Forward<Args>(args)...} );
}
} //ns Log::Private

/*
template<typename... Args>
static FString const FormatString(Args&&... args)
{
    return Private::FormatString(KCINFO, Forward<Args>(args)...);
}
*/

// Convenience Log:: functions
template<typename... Args>
static void Debug(FString const& message, Args&&... args)
{
    namespace LOG = KC::LOG::DEBUG;
    
    FString const formatted_message =
        Private::FormatString( message, Forward<Args>(args)... );
    Private::LogToScreen( LOG::DURATION, LOG::COLOR, formatted_message );
    UE_LOG(KCLog, Verbose, TEXT("%s"), *formatted_message);
}

template<typename... Args>
static void Info(FString const& message, Args&&... args)
{
    namespace LOG = KC::LOG::INFO;
    
    FString const formatted_message =
        Private::FormatString( message, Forward<Args>(args)... );
    Private::LogToScreen( LOG::DURATION, LOG::COLOR, formatted_message );
    UE_LOG(KCLog, Log, TEXT("%s"), *formatted_message);
}

template<typename... Args>
static void Warn(FString const& message, Args&&... args)
{
    namespace LOG = KC::LOG::WARN;
    
    FString const formatted_message =
        Private::FormatString( message, Forward<Args>(args)... );
    Private::LogToScreen( LOG::DURATION, LOG::COLOR, formatted_message );
    UE_LOG(KCLog, Warning, TEXT("%s"), *formatted_message);
}

template<typename... Args>
static void Error( FString const& message, Args&&... args )
{
    namespace LOG = KC::LOG::ERROR;
    
    FString const formatted_message =
        Private::FormatString( message, Forward<Args>(args)... );
    Private::LogToScreen( LOG::DURATION, LOG::COLOR, formatted_message );
    UE_LOG(KCLog, Error, TEXT("%s"), *formatted_message);
}

template<typename... Args>
static void Fatal( FString const& message, Args&&... args )
{
    namespace LOG = KC::LOG::FATAL;
    
    FString const formatted_message =
        Private::FormatString( message, Forward<Args>(args)... );
    Private::LogToScreen( LOG::DURATION, LOG::COLOR, formatted_message );
    UE_LOG(KCLog, Fatal, TEXT("%s"), *formatted_message);
}

} // END Log
