// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PAWeapon.h"
#include "SkeletalGun.generated.h"

#define COLLISION_WEAPON ECC_GameTraceChannel1

class UGunWeaponConfig;
DECLARE_LOG_CATEGORY_EXTERN(WeaponGun, Display, All);

class USkeletalMeshComponent;

UCLASS(Abstract)
class PROJECTA_API ASkeletalGun : public APAWeapon
{
	GENERATED_BODY()
	
public:
	ASkeletalGun();

	virtual void SetWeaponConfig(UBaseWeaponConfig* NewWeaponConfig) override;
	virtual FTransform GetShotSocketTransform();

	AController* GetOwnerController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Mesh")
	USkeletalMeshComponent* WeaponMesh;



#pragma region Shoot
public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;
	
protected:
	virtual void MakeShot();
	void MakeDamage(FHitResult& HitResult);

private:
	FTimerHandle ShootTimer;
	
	UPROPERTY()
	const UGunWeaponConfig* GunWeaponConfig;
#pragma endregion 
	
};
