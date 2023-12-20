#pragma once

#include "WeaponAmmoStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponAmmo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (ClampMin = 1))
	int32 Ammo = 8;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (EditCondition = "!bInfinityClips" , ClampMin = 0))
	int32 Clips = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	bool bInfinityClips = false;
	
};
