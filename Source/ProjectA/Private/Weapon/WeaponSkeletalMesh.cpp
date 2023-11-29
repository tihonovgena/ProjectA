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

void AWeaponSkeletalMesh::BeginPlay()
{
	Super::BeginPlay();
}
