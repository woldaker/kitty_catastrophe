// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Poop.h"

// Sets default values
APoop::APoop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

