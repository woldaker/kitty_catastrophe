// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Kitty.h"


AKitty::AKitty()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AKitty::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKitty::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void AKitty::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

}

