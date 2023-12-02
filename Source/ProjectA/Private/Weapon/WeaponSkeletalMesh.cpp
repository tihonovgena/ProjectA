// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/WeaponSkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponSkeletalMesh::AWeaponSkeletalMesh()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (WeaponMesh)
	{
		SetRootComponent(WeaponMesh);
	}
}

FTransform AWeaponSkeletalMesh::GetShotSocketTransform()
{
	return WeaponMesh->GetSocketTransform(ShotSocketName);
}

void AWeaponSkeletalMesh::BeginPlay()
{
	Super::BeginPlay();
}
