// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SkeletalGun.h"
#include "RifleWeapon.generated.h"

UCLASS()
class PROJECTA_API ARifleWeapon : public ASkeletalGun
{
	GENERATED_BODY()

protected:
	virtual void MakeShot() override;
	
private:
	bool MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace);
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
};
