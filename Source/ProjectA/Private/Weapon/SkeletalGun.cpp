// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/SkeletalGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Weapon/WeaponConfig/GunWeaponConfig.h"

DEFINE_LOG_CATEGORY(WeaponGun)

ASkeletalGun::ASkeletalGun()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (WeaponMesh)
	{
		SetRootComponent(WeaponMesh);
	}
}

FTransform ASkeletalGun::GetShotSocketTransform()
{
	return WeaponMesh->GetSocketTransform(GetGunWeaponConfig()->ShotSocketName);
}

AController* ASkeletalGun::GetOwnerController()
{
	if (!GetOwner()) return nullptr;
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn)) return nullptr;
	return Pawn->GetController();
	
}

UGunWeaponConfig* ASkeletalGun::GetGunWeaponConfig()
{
	return Cast<UGunWeaponConfig>(GetWeaponConfig());
}

void ASkeletalGun::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void ASkeletalGun::StartAttack()
{
	GetWorldTimerManager().SetTimer
	(ShootTimer,this, &ASkeletalGun::MakeShot, GetGunWeaponConfig()->FireRate, true, -1);
}

void ASkeletalGun::StopAttack()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ASkeletalGun::MakeShot()
{
	
}

void ASkeletalGun::MakeDamage(FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (IsValid(DamagedActor))
	{
		DamagedActor->TakeDamage(10.0f, FDamageEvent(),GetOwnerController(), this);
	}
}


