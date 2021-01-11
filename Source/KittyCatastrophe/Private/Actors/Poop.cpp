// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Actors/Poop.h"


APoop::APoop()
{
	PrimaryActorTick.bCanEverTick = true;

}


void APoop::BeginPlay()
{
	Super::BeginPlay();
	
}


void APoop::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

