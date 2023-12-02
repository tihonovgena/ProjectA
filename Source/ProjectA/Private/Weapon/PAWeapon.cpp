// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/PAWeapon.h"

APAWeapon::APAWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

}

FTransform APAWeapon::GetShotSocketTransform()
{
	return FTransform();
}

void APAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

