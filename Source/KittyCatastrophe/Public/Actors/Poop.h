// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once
// Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// KC
//#include "Actors/Level/DamageCarrierComponent.h"
#include "Poop.generated.h"


UCLASS()
class KITTYCATASTROPHE_API APoop : public AActor/*ADamageCarrierComponent*/
{
	GENERATED_BODY()
public:
	APoop();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float deltaTime) override;
};
