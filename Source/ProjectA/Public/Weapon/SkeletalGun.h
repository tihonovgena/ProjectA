// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PAWeapon.h"
#include "SkeletalGun.generated.h"

class UGunWeaponConfig;
class USkeletalMeshComponent;

DECLARE_LOG_CATEGORY_EXTERN(WeaponGun, Display, All);

UCLASS(Abstract)
class PROJECTA_API ASkeletalGun : public APAWeapon
{
	GENERATED_BODY()
	
public:
	ASkeletalGun();
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
	UGunWeaponConfig* GetGunWeaponConfig();
	FTimerHandle ShootTimer;
	
#pragma endregion 
	
};
