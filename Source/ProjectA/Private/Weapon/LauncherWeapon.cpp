// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/LauncherWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Weapon/WeaponConfig/LauncherWeaponConfig.h"
#include "Weapon/Projectile/BaseProjectile.h"

ULauncherWeaponConfig* ALauncherWeapon::GetLauncherWeaponConfig()
{
	return Cast<ULauncherWeaponConfig>(GetWeaponConfig());
}

void ALauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform = GetShotSocketTransform();
	ABaseProjectile* Projectile = Cast<ABaseProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), GetLauncherWeaponConfig()->ProjectileClass, SpawnTransform));
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
