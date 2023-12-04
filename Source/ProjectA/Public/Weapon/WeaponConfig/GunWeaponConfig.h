// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponConfig/BaseWeaponConfig.h"
#include "GunWeaponConfig.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTA_API UGunWeaponConfig : public UBaseWeaponConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	FName ShotSocketName = "ShotSocket";

	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	float ShotDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	float FireRate = 0.5f;
};
