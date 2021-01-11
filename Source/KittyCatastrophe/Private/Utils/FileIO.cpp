// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Utils/FileIO.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

#include "Utils/Log.h"


bool UFileIO::TryLoadFileToString(FString& OutContents_, FString const& RelativePath_)
{
    static FString const CONTENT_DIR = FPaths::ProjectContentDir();
    IPlatformFile& filesystem = FPlatformFileManager::Get().GetPlatformFile();

    if (!filesystem.CreateDirectory(*CONTENT_DIR))
    {
        Log::Warn("Could not load file '{0}' to string: error reading from Content/ directory.", *RelativePath_);
        return false;
    }

    FString const filepath = CONTENT_DIR + TEXT("/") + RelativePath_;

    if (!FPaths::FileExists(filepath))
    {
        Log::Warn("Could not load file '{0}' to string: file doesn't exist.", *RelativePath_);
        return false;
    }

    return FFileHelper::LoadFileToString(OutContents_, *filepath);
}


bool UFileIO::TryLoadFileToStringArray(TArray<FString>& OutContents_, FString const& RelativePath_)
{
    static FString const CONTENT_DIR = FPaths::ProjectContentDir();
    IPlatformFile& filesystem = FPlatformFileManager::Get().GetPlatformFile();

    if (!filesystem.CreateDirectory(*CONTENT_DIR))
    {
        Log::Warn("Could not load file '{0}' to string array: error reading from Content/ directory.", *RelativePath_);
        return false;
    }

    FString const filepath = CONTENT_DIR + TEXT("/") + RelativePath_;

    if (!FPaths::FileExists(filepath))
    {
        Log::Warn("Could not load file '{0}' to string array: file doesn't exist.", *RelativePath_);
        return false;
    }

    return FFileHelper::LoadFileToStringArray(OutContents_, *filepath);
}
