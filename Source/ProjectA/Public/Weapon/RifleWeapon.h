// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SkeletalGun.h"
#include "RifleWeapon.generated.h"

class URifleWeaponConfig;

#define UE_COLLISION_WEAPON ECC_GameTraceChannel1

UCLASS()
class PROJECTA_API ARifleWeapon : public ASkeletalGun
{
	GENERATED_BODY()
	
public:
	URifleWeaponConfig* GetRifleWeaponConfig();

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	
private:
	bool MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace);
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
	
};
