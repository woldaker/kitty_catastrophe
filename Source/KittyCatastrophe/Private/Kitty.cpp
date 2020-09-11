// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Kitty.h"

// Sets default values
AKitty::AKitty()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKitty::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKitty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKitty::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

