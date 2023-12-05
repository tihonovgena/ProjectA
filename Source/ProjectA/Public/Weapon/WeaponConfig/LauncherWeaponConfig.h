// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GunWeaponConfig.h"
#include "LauncherWeaponConfig.generated.h"


class ABaseProjectile;

UCLASS()
class PROJECTA_API ULauncherWeaponConfig : public UGunWeaponConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABaseProjectile> ProjectileClass;
	
};
