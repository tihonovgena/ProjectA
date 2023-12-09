// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseInputConfigAsset.generated.h"

class UInputAction;

/**
 * Store pointer to Input Action for native binding
 */
UCLASS()
class PROJECTA_API UBaseInputConfigAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* SwitchWeapon;
};
