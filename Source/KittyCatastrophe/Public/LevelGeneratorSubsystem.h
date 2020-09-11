// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelGeneratorSubsystem.generated.h"

class UFloorSectionMap;

UCLASS(DisplayName="Level Generator Subsystem")
class KITTYCATASTROPHE_API ULevelGeneratorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//virtual void Deinitialize() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoaded);

	UPROPERTY(BlueprintAssignable, Category=LevelGeneratorSubsystem)
	FLevelLoaded OnLevelLoaded;

	UFUNCTION(BlueprintCallable, Category=LevelGeneratorSubsystem)
	void LoadLevel(UFloorSectionMap* level);

	UFUNCTION(BlueprintCallable, Category=LevelGeneratorSubsystem)
	void ClearLevel();

private:
	TArray<AActor*> Actors;
};
