// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poop.generated.h"

UCLASS()
class KITTYCATASTROPHE_API APoop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
