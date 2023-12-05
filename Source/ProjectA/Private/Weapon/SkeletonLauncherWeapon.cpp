// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/SkeletonLauncherWeapon.h"
#include "Weapon/WeaponConfig/LauncherWeaponConfig.h"

ASkeletonLauncherWeapon::ASkeletonLauncherWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (WeaponMesh)
	{
		SetRootComponent(WeaponMesh);
	}
}

FTransform ASkeletonLauncherWeapon::GetShotSocketTransform()
{
	return WeaponMesh->GetSocketTransform(GetLauncherWeaponConfig()->ShotSocketName);
}

void ASkeletonLauncherWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	
}

