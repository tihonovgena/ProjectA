// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/PAWeapon.h"

void APAWeapon::StartAttack()
{
	
}

void APAWeapon::StopAttack()
{
	
}

void APAWeapon::SetWeaponConfig(UBaseWeaponConfig* NewWeaponConfig)
{
	check(NewWeaponConfig);
	WeaponConfig = NewWeaponConfig;
}

UBaseWeaponConfig* APAWeapon::GetWeaponConfig()
{
	return WeaponConfig;
}

void APAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

