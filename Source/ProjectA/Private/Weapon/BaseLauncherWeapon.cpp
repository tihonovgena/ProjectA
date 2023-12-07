// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/BaseLauncherWeapon.h"
#include "Weapon/WeaponConfig/LauncherWeaponConfig.h"
#include "Weapon/Projectile/BaseProjectile.h"

ULauncherWeaponConfig* ABaseLauncherWeapon::GetLauncherWeaponConfig()
{
	return Cast<ULauncherWeaponConfig>(GetWeaponConfig());
}

void ABaseLauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform = GetShotSocketTransform();
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(GetLauncherWeaponConfig()->ProjectileClass, SpawnTransform);
	Projectile->SetMoveDirection(GetShotSocketTransform().GetRotation().GetForwardVector());
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);
}
