// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SkeletalGun.h"
#include "LauncherWeapon.generated.h"


class ULauncherWeaponConfig;

UCLASS()
class PROJECTA_API ALauncherWeapon : public ASkeletalGun
{
	GENERATED_BODY()

public:
	ULauncherWeaponConfig* GetLauncherWeaponConfig();
	
protected:
	virtual void MakeShot() override;
};
