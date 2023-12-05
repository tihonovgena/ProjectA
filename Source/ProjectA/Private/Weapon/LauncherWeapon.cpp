// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/LauncherWeapon.h"
#include "Weapon/WeaponConfig/LauncherWeaponConfig.h"
#include "Weapon/Projectile/BaseProjectile.h"

ULauncherWeaponConfig* ALauncherWeapon::GetLauncherWeaponConfig()
{
	return Cast<ULauncherWeaponConfig>(GetWeaponConfig());
}

void ALauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform = GetShotSocketTransform();
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(GetLauncherWeaponConfig()->ProjectileClass, SpawnTransform);
	Projectile->SetMoveDirection(GetShotSocketTransform().GetRotation().GetForwardVector());
	Projectile->FinishSpawning(SpawnTransform);
}
