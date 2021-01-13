// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "Containers/UnrealString.h"
// KC
#include "Config/Constants/Base.h"


namespace KC {
namespace /*KC::*/ PATH {
FString const ROOT = KC::PROJECT_NAME + TEXT("/");

// Directories in Content/
FString const CORE             = ROOT + TEXT("Core/");
FString const CHARACTERS       = ROOT + TEXT("Characters/");
FString const INTERACTABLES    = ROOT + TEXT("Interactables/");
FString const ENVIRONMENT      = ROOT + TEXT("Environment/");
FString const LEVELS           = ROOT + TEXT("Levels/");
FString const MATERIAL_LIBRARY = ROOT + TEXT("MaterialLibrary/");
FString const UI               = ROOT + TEXT("UI/");
// Subdirectories
FString const ENGINE    = CORE   + TEXT("Engine/");
FString const LEVELMAPS = LEVELS + TEXT("Maps/");


// MARK: Add new BP class info here
namespace /*KC::PATH::*/ ASSET {
FString const ROOT = TEXT("/Game/") + PATH::ROOT;

FString ConstructPath(
    FString const& assetType,
    FString const& dir,
    FString const& className
);


namespace /*KC::PATH::ASSET::*/ DATATABLE {
constexpr TCHAR const* TYPENAME = TEXT("DataTable");

constexpr TCHAR const*      LURE = TEXT("DT_BPClass_Lure");
constexpr TCHAR const* FLOORTILE = TEXT("DT_BPClass_FloorTile");
constexpr TCHAR const*  WALLTILE = TEXT("DT_BPClass_WallTile");

enum class /*KC::PATH::ASSET::DATATABLE::*/ TYPE : uint8
{
    LURE,
    FLOORTILE,
    WALLTILE,

    MAX
};

FString ClassName( TYPE const base );
FString ConstructPath( TYPE const base );
} //ns KC::PATH::ASSET::DATATABLE

namespace /*KC::PATH::ASSET::*/ STATIC_MESH {
constexpr TCHAR const* TYPENAME = TEXT("StaticMesh");

constexpr TCHAR const* TROUGH          = TEXT("SM_Trough");
constexpr TCHAR const* TROUGH_CONTENTS = TEXT("SM_TroughContents");
constexpr TCHAR const* WALL_PLANE      = TEXT("SM_WallPlane");

enum class /*KC::PATH::ASSET::STATIC_MESH::*/ TYPE : uint8
{
    TROUGH,
    TROUGH_CONTENTS,
    WALL_PLANE,

    MAX
};

FString ClassName( TYPE const base );
FString ConstructPath( TYPE const base );


namespace /*KC::PATH::ASSET::STATIC_MESH::*/ ENGINE {
FString const BASIC_PLANE = ASSET::ConstructPath(
    STATIC_MESH::TYPENAME,
    TEXT("/Engine/BasicShapes/"),
    TEXT("Plane")
);
} //ns KC::PATH::ASSET::STATIC_MESH::ENGINE

} //ns KC::PATH::ASSET::STATIC_MESH
} //ns KC::PATH::ASSET

} //ns KC::PATH
} //ns KC
