// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>


#include "MyPlayerController.h"

#include "Engine/DataTable.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"
#include "Templates/SubclassOf.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

#include "Inventory.h"
#include "Lure.h"
#include "MyDeveloperSettings.h"
#include "MyPlayerState.h"
#include "Utils/Log.h"


AMyPlayerController::AMyPlayerController()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DT_LureClasses(TEXT(PATH_DATA_TABLE_LURE_CLASSES));
    if (DT_LureClasses.Succeeded())
    {
        LureClasses = DT_LureClasses.Object;
    }
    else
    {
        Log::Error("Could not instantiate Lure class data tale in MyPlayerController.");
    }
}


void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction(TEXT(INPUT_ACTION_MAPPING_TOUCH_1), EInputEvent::IE_Pressed, this, &AMyPlayerController::OnTouchPressed);
    InputComponent->BindAction(TEXT(INPUT_ACTION_MAPPING_TOUCH_1), EInputEvent::IE_Released, this, &AMyPlayerController::OnTouchReleased);
}


void AMyPlayerController::OnTouchPressed()
{
    FHitResult HitResult;
    if (!GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Visibility, false, HitResult))
    {
        Log::Warn("Couldn't get hit result under touch input.");
        return;
    }

    ELureType CurrentLureType = Cast<AMyPlayerState>(PlayerState)->GetInventory()->GetActiveLureType();
    
    FVector SpawnLoc(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, 150.0f);
    FRotator SpawnRot(0.0f, 0.0f, 0.0f);

    if (LureClasses)
    {
        FString const DT_Context = TEXT("Datatable Lure Classes Context");
        FLureClassLUT* LureClassLUT = LureClasses->FindRow<FLureClassLUT>(*ELureType_::GetName(CurrentLureType), DT_Context);

        if (!LureClassLUT)
        {
            Log::Warn("Couldn't find row in LureClassLUT with name '{0}'", *ELureType_::GetName(CurrentLureType));
            return;
        }

        SpawnedLure = GetWorld()->SpawnActor<ALure>(LureClassLUT->BPClass, SpawnLoc, SpawnRot);
        if (!SpawnedLure)
        {
            Log::Warn("Spawning Lure failed");
            return;
        }

        GetWorldTimerManager().SetTimer(TimerHandleUpdateSpawnLocation, this, &AMyPlayerController::UpdateSpawnLocation, 0.1f, true, 0.0f);
    }
}


void AMyPlayerController::UpdateSpawnLocation()
{
    if (!SpawnedLure)
    {
        Log::Warn("Spawned lure cannot be moved because it no longer exists.");
        return;
    }

    FHitResult HitResult;
    if (!GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Visibility, false, HitResult))
    {
        Log::Warn("Couldn't get hit result under touch input drag.");
        return;
    }

    SpawnedLure->SetActorLocation(FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, 150.0f));
}


void AMyPlayerController::OnTouchReleased()
{
    GetWorldTimerManager().ClearTimer(TimerHandleUpdateSpawnLocation);

    if (SpawnedLure)
    {
        SpawnedLure->Activate();
    }
}
