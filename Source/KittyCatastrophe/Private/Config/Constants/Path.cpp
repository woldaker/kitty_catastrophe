// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Config/Constants/Path.h"


FString KC::PATH::ASSET::ConstructPath(
    FString const& assetType,
    FString const& dir,
    FString const& className
) {
    return assetType + TEXT("'") + dir + className + TEXT(".") + className + TEXT("'");
}


FString KC::PATH::ASSET::DATATABLE::ClassName( DATATABLE::TYPE const base )
{
    using DT_TYPE = DATATABLE::TYPE;
    
    switch(base)
    {
    case DT_TYPE::LURE:
        return DATATABLE::LURE;
    case DT_TYPE::FLOORTILE:
        return DATATABLE::FLOORTILE;
    case DT_TYPE::WALLTILE:
        return DATATABLE::WALLTILE;
    default:
        checkNoEntry();
        return {};
    }
}


FString KC::PATH::ASSET::DATATABLE::ConstructPath( DATATABLE::TYPE const base )
{
    static FString const DT_ROOT_DIR = ASSET::ROOT + TEXT("Core/Data/");
    return ASSET::ConstructPath(
        DATATABLE::TYPENAME,
        DT_ROOT_DIR,
        DATATABLE::ClassName( base )
    );
}


FString KC::PATH::ASSET::STATIC_MESH::ClassName( STATIC_MESH::TYPE const base )
{
    using SM_TYPE = STATIC_MESH::TYPE;
    
    switch(base)
    {
    case SM_TYPE::TROUGH:
        return STATIC_MESH::TROUGH;
    case SM_TYPE::TROUGH_CONTENTS:
        return STATIC_MESH::TROUGH_CONTENTS;
    default:
        checkNoEntry();
        return {};
    }
}


FString KC::PATH::ASSET::STATIC_MESH::ConstructPath( STATIC_MESH::TYPE const base )
{
    static FString const SM_ROOT_DIR = ASSET::ROOT + TEXT("Core/Interactables/");
    return ASSET::ConstructPath(
        STATIC_MESH::TYPENAME,
        SM_ROOT_DIR,
        STATIC_MESH::ClassName( base )
    );
}
