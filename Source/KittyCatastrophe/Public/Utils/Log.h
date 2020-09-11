// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "Engine.h"
#include "Containers/UnrealString.h"
#include "Utils/Constants.h"


namespace Log
{
namespace Internal
{

static void LogToScreen(float const duration, FColor const color, FString const& message)
{
    if (!GEngine)
    {
        UE_LOG(LogTemp, Warning, TEXT("GEngine not available for printing to screen.  Message: '%s'"), *message);
        return;
    }

    GEngine->AddOnScreenDebugMessage(INDEX_NONE, duration, color, message);
}


static FString FormatString(FString const& message)
{
    return message;
}


template <typename... Args>
static FString FormatString(FString const& message, Args&&... args)
{
    TArray<FStringFormatArg> format_args {Forward<Args>(args)...};
    return FString::Format(*message, format_args);
}

} // END Log::Internal


template<typename... Args>
static void Info(FString const& message, Args&&... args)
{
    FString formatted_message = Internal::FormatString(message, Forward<Args>(args)...);
    Internal::LogToScreen(Constants::Log::Info::MSG_DURATION, Constants::Log::Info::MSG_COLOR, formatted_message);
    UE_LOG(LogTemp, Display, TEXT("%s"), *formatted_message);
}


template<typename... Args>
static void Warn(FString const& message, Args&&... args)
{
    FString formatted_message = Internal::FormatString(message, Forward<Args>(args)...);
    Internal::LogToScreen(Constants::Log::Warn::MSG_DURATION, Constants::Log::Warn::MSG_COLOR, formatted_message);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *formatted_message);
}


template<typename... Args>
static void Error(FString const& message, Args&&... args)
{
    FString formatted_message = Internal::FormatString(message, Forward<Args>(args)...);
    Internal::LogToScreen(Constants::Log::Error::MSG_DURATION, Constants::Log::Error::MSG_COLOR, formatted_message);
    UE_LOG(LogTemp, Error, TEXT("%s"), *formatted_message);
}

} // END Log
