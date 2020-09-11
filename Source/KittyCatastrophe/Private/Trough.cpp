// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Trough.h"

#include "Engine/EngineTypes.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyDeveloperSettings.h"


ATrough::ATrough()
{
	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(false);

	Trough = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trough"));
	TroughContents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trough Contents"));
	
	RootComponent = Trough;
	TroughContents->SetupAttachment(Trough);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TroughMesh(TEXT(PATH_STATIC_MESH_TROUGH));
    if (TroughMesh.Succeeded())
	{
        Trough->SetStaticMesh(TroughMesh.Object);
		TROUGH_HEIGHT = TroughMesh.Object->GetBoundingBox().GetExtent().Z;
    }

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TroughContentsMesh(TEXT(PATH_STATIC_MESH_TROUGH_CONTENTS));
    if (TroughContentsMesh.Succeeded())
	{
        TroughContents->SetStaticMesh(TroughContentsMesh.Object);
    }

	Trough->SetAutoActivate(true);
	Trough->SetGenerateOverlapEvents(false);
    Trough->SetMobility(EComponentMobility::Static);
    Trough->SetReceivesDecals(false);
	Trough->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Trough->BodyInstance.SetObjectType(ECC_WorldDynamic);
    Trough->BodyInstance.SetResponseToAllChannels(ECR_Block);

    TroughContents->bUseAttachParentBound = true;
	TroughContents->SetAutoActivate(true);
    TroughContents->SetCanEverAffectNavigation(false);
	TroughContents->SetGenerateOverlapEvents(false);
    TroughContents->SetMobility(EComponentMobility::Movable);
	TroughContents->SetReceivesDecals(false);
    TroughContents->BodyInstance.bLockXTranslation = true;
    TroughContents->BodyInstance.bLockYTranslation = true;
    TroughContents->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TroughContents->BodyInstance.SetEnableGravity(false);
	TroughContents->BodyInstance.SetObjectType(ECC_WorldDynamic);
	TroughContents->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
}


void ATrough::Fill(float Percent)
{
	PercentFull = Percent;

	float ContentHeight = (Percent / 100.0f) * TROUGH_HEIGHT;
	TroughContents->SetRelativeLocation(FVector(0.0f, 0.0f, ContentHeight));
}
