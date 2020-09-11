// Copyright Wesley H. Oldaker <wesleyoldaker@gmail.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trough.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract, Blueprintable, ClassGroup="Troughs", meta=(IsBlueprintBase="true"))
class KITTYCATASTROPHE_API ATrough : public AActor
{
	GENERATED_BODY()
	
public:
	ATrough();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Trough;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TroughContents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Interp, Transient, Category="State", meta=(ClampMin="0.0", ClampMax="100.0", DisplayName="Percent Full", ExposeOnSpawn="true"))
	float PercentFull = 0.0f;

	UFUNCTION(BlueprintCallable, CallInEditor, Category="State", meta=(ToolTip="Fills the trough to the percentage specified"))
	virtual void Fill(
		UPARAM(DisplayName="Percent Full", meta=(ClampMin="0.0", ClampMax="100.0")) float Percent
	) final;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category="Constants", meta=(ClampMin="0.0", DisplayName="TROUGH HEIGHT", ToolTip="Distance from the base to the brim of the trough.  Used for calculating translations from fill percentage."))
	float TROUGH_HEIGHT = 0.0f;
};
