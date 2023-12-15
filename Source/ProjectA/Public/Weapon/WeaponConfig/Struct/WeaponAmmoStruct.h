#pragma once

#include "CoreMinimal.h"
#include "WeaponAmmoStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponAmmo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Ammo", meta = (ClampMin = 0))
	int32 Ammo = 8;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ammo", meta = (EditCondition = "!bInfinityClips" , ClampMin = 0))
	int32 Clips = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	bool bInfinityClips = false;
	
};
