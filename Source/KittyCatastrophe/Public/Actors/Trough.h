// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Trough.generated.h"

//class UStaticMeshComponent;


UCLASS(Abstract, Blueprintable, Category="Interactables", ClassGroup="Troughs", meta=(IsBlueprintBase="true", DisplayName="Trough", ToolTip="Base class for Food Trough and Litter Box."))
class KITTYCATASTROPHE_API ATrough : public AActor
{
	GENERATED_BODY()
	
public:
	ATrough();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Trough = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TroughContents = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Interp, Transient, Category="State", meta=(ClampMin=0.0f, ClampMax=100.0f, DisplayName="Percent Full", ExposeOnSpawn="true"))
	float PercentFull = 0.0f;

	UFUNCTION(BlueprintCallable, CallInEditor, Category="State", meta=(DisplayName="Fill", ToolTip="Fills the trough to the percentage specified."))
	virtual void Fill(
		UPARAM(DisplayName="Percentage")
        float percentage
	) final;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category="Constants", meta=(ClampMin=0.0f, DisplayName="Trought Height", ToolTip="Distance from the base to the brim of the trough.  Used for calculating translations from fill percentage."))
	float TROUGH_HEIGHT = 0.0f;
};
