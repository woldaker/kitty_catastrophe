// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "KCHUD_InGame.generated.h"


UCLASS()
class KITTYCATASTROPHE_API AKCHUD_InGame : public AHUD
{
    GENERATED_BODY()
public:
    AKCHUD_InGame();

    // Primary draw call for the HUD.
    virtual void DrawHUD() override;
    virtual void BeginPlay() override;
    virtual void Tick(float deltaSeconds) override;

    //UFUNCTION()
    //void UpdateComboCount(int32 Value);

    //UFUNCTION()
    //void ResetCombo();
    //UPROPERTY(EditDefaultsOnly, Category = "Interactive")
    //TSubclassOf<UUserWidget> HitComboWidgetClass;
//private:
    //UHitComboWidget* HitComboWidget;
};
