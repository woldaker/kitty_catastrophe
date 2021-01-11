// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(KCLog, Log, All);

/*
NAMING CONVENTIONS:

namespace SomeNamespace {
struct Foo {};
}

// KC is Kitty Catastrophe's main custom namespace
namespace KC {
// Usually subdivided into other topical namespaces
namespace TOPIC {

namespace SUBTOPIC_A { // ...

// reminder that we're past the main topic namespace KC::TOPIC :
// SUBTOPIC_A::
namespace SUBTOPIC_B {
} // ::SUBTOPIC_A::SUBTOPIC_B
// ^ bookend reminder


UCLASS(meta=(DisplayName="Bar", ToolTip="bar!")) // <-- MOST U-macros should specify a DisplayName and ToolTip
class ABar : public AActor
{
    GENERATED_BODY()
public:
    UFUNCTION(meta=(DisplayName="Do Stuff", ToolTip="does some stuff"))
    SomeNamespace::Foo DoStuff(int32 Parameter1_, int32& OutParameter_) // <-- TODO: Should OutParameter_ always be last?...
    {
        namespace FooSpace = SomeNamespace;
        namespace FOR_CONSTANTS = KC::TOPIC;
        
        FooSpace::Foo local_variable;
 
        Log::Warn("No TEXT() macro used here.  Suck it, {0}!", TEXT("nerd"));
        
        return local_variable;
    }
private:
    UPROPERTY(meta=(DisplayName="Member Variable", ToolTip="useful info here"))
    int32 MemberVariable = 234; // <-- Set default values for member variables inline in the header
};
*/
