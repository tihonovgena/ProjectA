// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PAWeapon.h"
#include "WeaponConfig/Struct/WeaponAmmoStruct.h"
#include "BaseGunWeapon.generated.h"

class UGunWeaponConfig;
class USkeletalMeshComponent;

DECLARE_LOG_CATEGORY_EXTERN(WeaponGun, Display, All);

UCLASS(Abstract)
class PROJECTA_API ABaseGunWeapon : public APAWeapon
{
	GENERATED_BODY()
	
public:
	virtual FTransform GetShotSocketTransform();
	AController* GetOwnerController();

protected:
	virtual void BeginPlay() override;

#pragma region Ammo
public:
	void WeaponReload();
	
protected:
	bool HasAmmo() const;
	bool HasClips() const;
	bool AreClipsInfinity() const;
	bool CanBeReloaded() const;
	
private:
	void SetupWeaponAmmo();
	
	UPROPERTY()
	FWeaponAmmo WeaponAmmoStruct;
	
#pragma endregion 
	
#pragma region Shoot
public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;
	
protected:
	virtual void Shot();
	
	void MakeDamage(FHitResult& HitResult);

private:
	virtual void MakeShot();
	UGunWeaponConfig* GetGunWeaponConfig();
	FTimerHandle ShootTimer;
	
#pragma endregion 
	
};
