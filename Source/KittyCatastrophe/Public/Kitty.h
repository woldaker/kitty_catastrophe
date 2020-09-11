// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kitty.generated.h"

UCLASS()
class KITTYCATASTROPHE_API AKitty : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKitty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
