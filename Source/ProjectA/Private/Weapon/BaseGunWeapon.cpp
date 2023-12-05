// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/BaseGunWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Weapon/WeaponConfig/GunWeaponConfig.h"

DEFINE_LOG_CATEGORY(WeaponGun)

FTransform ABaseGunWeapon::GetShotSocketTransform()
{
	return FTransform();
}

AController* ABaseGunWeapon::GetOwnerController()
{
	if (!GetOwner()) return nullptr;
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn)) return nullptr;
	return Pawn->GetController();
	
}

UGunWeaponConfig* ABaseGunWeapon::GetGunWeaponConfig()
{
	return Cast<UGunWeaponConfig>(GetWeaponConfig());
}

void ABaseGunWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGunWeapon::StartAttack()
{
	GetWorldTimerManager().SetTimer
	(ShootTimer,this, &ABaseGunWeapon::MakeShot, GetGunWeaponConfig()->FireRate, true, -1);
}

void ABaseGunWeapon::StopAttack()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ABaseGunWeapon::MakeShot()
{
	
}

void ABaseGunWeapon::MakeDamage(FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (IsValid(DamagedActor))
	{
		DamagedActor->TakeDamage(10.0f, FDamageEvent(),GetOwnerController(), this);
	}
}


