// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#include "Core/KCPlayerController.h"
// Engine
#include "Engine/DataTable.h"
#include "TimerManager.h"
// KC
#include "Actors/Inventory.h"
#include "Actors/Lure.h"
#include "Config/KCDeveloperSettings.h"
#include "Config/Constants/Input.h"
#include "Config/Constants/Path.h"
#include "Core/KCPlayerState.h"
#include "Data/LUTEntry_BPClass_Lure.h"
#include "Utils/Log.h"


AKCPlayerController::AKCPlayerController()
{
    namespace DT = KC::PATH::ASSET::DATATABLE;

    static ConstructorHelpers::FObjectFinder<UDataTable> dtBPLure (
        *DT::ConstructPath( DT::TYPE::LURE )
    );
    checkf(dtBPLure.Succeeded(), TEXT("Could not instantiate Lure BPClass DataTable."));
    
    DT_BPLure = dtBPLure.Object;
}


void AKCPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    namespace INPUT = KC::INPUT::MAPPING;

    InputComponent->BindAction(
        INPUT::TOUCH_1,
        EInputEvent::IE_Pressed,
        this,
        &AKCPlayerController::OnTouchPressed
    );
    
    InputComponent->BindAction(
        INPUT::TOUCH_1,
        EInputEvent::IE_Released,
        this,
        &AKCPlayerController::OnTouchReleased
    );
}


void AKCPlayerController::OnTouchPressed()
{
    if (!DT_BPLure)
    {
        Log::Info( "Nothing to do on touch pressed: Lure class LUT not defined." );
        return;
    }

    FHitResult hitResult;
    if (!GetHitResultUnderFinger(
            ETouchIndex::Type::Touch1,
            ECollisionChannel::ECC_Visibility,
            false,
            hitResult
        )
    ) {
        Log::Info( "Couldn't get hit result under touch input." );
        return;
    }

    AKCPlayerState* playerState = GetPlayerState<AKCPlayerState>();
    checkf(playerState, TEXT("Player state is null."));
    
    UInventory* inventory = playerState->GetInventory();
    checkf(inventory, TEXT("Inventory is null."));
    
    ELure currentLure = inventory->GetActiveLureType();
    FString currentLureName = FString{ Lure::GetName( currentLure ) };
    currentLureName.RemoveSpacesInline();
    
    UKCDeveloperSettings const* CFG = GetDefault<UKCDeveloperSettings>();
    checkf(CFG, TEXT("Couldn't get DeveloperSettings."));
    
    FVector spawnLoc =
    {
        hitResult.ImpactPoint.X,
        hitResult.ImpactPoint.Y,
        CFG->LureDropHeight
    };
    
    FRotator spawnRot = FRotator::ZeroRotator;
    
    constexpr TCHAR const* DT_LURE_CONTEXT = TEXT("Lure Class LUT");
    FLUTEntry_BPClass_Lure* lureData = DT_BPLure->FindRow<FLUTEntry_BPClass_Lure>(
        *currentLureName,
        DT_LURE_CONTEXT
    );

    if (!lureData)
    {
        Log::Warn( "Couldn't find row in LUT_Lure with name '{0}'", currentLureName );
        return;
    }
    
    TSubclassOf<ALure> lureClass = lureData->BPClass;
    checkf(lureClass, TEXT("Lure subclass in data table is null."));

    UWorld* world = GetWorld();
    checkf(world, TEXT("World is null."));
    
    SpawnedLure = world->SpawnActor<ALure>( lureClass, spawnLoc, spawnRot );
    if (!SpawnedLure)
    {
        Log::Warn( "Spawning Lure failed" );
        return;
    }

    GetWorldTimerManager().SetTimer(
        Timer_UpdateSpawnLocation,
        this,
        &AKCPlayerController::UpdateSpawnLocation,
        0.1f,
        true,
        0.0f
    );
}


void AKCPlayerController::UpdateSpawnLocation()
{
    if (!IsValid( SpawnedLure ))
    {
        Log::Info( "Spawned lure cannot be moved because it no longer exists." );
        return;
    }

    FHitResult hitResult;
    if (!GetHitResultUnderFinger(
            ETouchIndex::Type::Touch1,
            ECollisionChannel::ECC_Visibility,
            false,
            hitResult
        )
    ) {
        Log::Info( "Couldn't get hit result under touch input drag." );
        return;
    }

    UKCDeveloperSettings const* CFG = GetDefault<UKCDeveloperSettings>();
    checkf(CFG, TEXT("Couldn't get DeveloperSettings."));
    
    SpawnedLure->SetActorLocation(
        FVector{
            hitResult.ImpactPoint.X,
            hitResult.ImpactPoint.Y,
            CFG->LureDropHeight
        }
    );
}


void AKCPlayerController::OnTouchReleased()
{
    GetWorldTimerManager().ClearTimer( Timer_UpdateSpawnLocation );

    if (SpawnedLure)
    {
        SpawnedLure->Activate();
    }
}
