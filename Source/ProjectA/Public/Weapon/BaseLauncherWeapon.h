// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseGunWeapon.h"
#include "BaseLauncherWeapon.generated.h"


class ULauncherWeaponConfig;

UCLASS(Abstract)
class PROJECTA_API ABaseLauncherWeapon : public ABaseGunWeapon
{
	GENERATED_BODY()

public:
	ULauncherWeaponConfig* GetLauncherWeaponConfig();
	
protected:
	virtual void Shot() override;
};
