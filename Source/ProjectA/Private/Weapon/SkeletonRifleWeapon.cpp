// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/SkeletonRifleWeapon.h"
#include "Weapon/WeaponConfig/RifleWeaponConfig.h"


ASkeletonRifleWeapon::ASkeletonRifleWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (WeaponMesh)
	{
		SetRootComponent(WeaponMesh);
	}
}

FTransform ASkeletonRifleWeapon::GetShotSocketTransform()
{
	return WeaponMesh->GetSocketTransform(GetRifleWeaponConfig()->ShotSocketName);
}

void ASkeletonRifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	
}
