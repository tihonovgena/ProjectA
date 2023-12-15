// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseGunWeapon.h"
#include "BaseRifleWeapon.generated.h"

class URifleWeaponConfig;

#define UE_COLLISION_WEAPON ECC_GameTraceChannel1

UCLASS(Abstract)
class PROJECTA_API ABaseRifleWeapon : public ABaseGunWeapon
{
	GENERATED_BODY()
	
public:
	URifleWeaponConfig* GetRifleWeaponConfig();

protected:
	virtual void BeginPlay() override;
	virtual void Shot() override;
	
private:
	bool MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace);
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
	
};
