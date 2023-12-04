// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PAWeapon.h"
#include "SkeletalGun.generated.h"

#define COLLISION_WEAPON ECC_GameTraceChannel1

DECLARE_LOG_CATEGORY_EXTERN(WeaponGun, Display, All);

class USkeletalMeshComponent;

UCLASS()
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

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName ShotSocketName = "ShotSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float ShotDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float FireRate = 0.5f;

#pragma region Shoot
public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;
	
protected:
	virtual void MakeShot();
	
	void MakeDamage(FHitResult& HitResult);
	
	bool MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace);
	
private:
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
	
	FTimerHandle ShootTimer;
	
#pragma endregion 
	
};
