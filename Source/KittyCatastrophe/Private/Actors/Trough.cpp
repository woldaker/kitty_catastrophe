// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "Actors/Trough.h"

#include "Config/Constants/Path.h"


ATrough::ATrough()
{
    namespace SM = KC::PATH::ASSET::STATIC_MESH;

	PrimaryActorTick.bCanEverTick = true;
	SetCanBeDamaged(false);

	Trough = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trough"));
	TroughContents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trough Contents"));
	
	RootComponent = Trough;
	TroughContents->SetupAttachment(Trough);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> troughMesh(*SM::ConstructPath(SM::TYPE::TROUGH));
    if (troughMesh.Succeeded())
	{
        Trough->SetStaticMesh(troughMesh.Object);
		TROUGH_HEIGHT = troughMesh.Object->GetBoundingBox().GetSize().Z;
    }

	static ConstructorHelpers::FObjectFinder<UStaticMesh> troughContentsMesh(*SM::ConstructPath(SM::TYPE::TROUGH_CONTENTS));
    if (troughContentsMesh.Succeeded())
	{
        TroughContents->SetStaticMesh(troughContentsMesh.Object);
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


void ATrough::Fill(float percentage)
{
	PercentFull = FMath::Clamp(percentage, 0.0f, 100.0f);

	float contentsHeight = (PercentFull / 100.0f) * TROUGH_HEIGHT;
	TroughContents->SetRelativeLocation(
        FVector(0.0f, 0.0f, contentsHeight)
    );
}
