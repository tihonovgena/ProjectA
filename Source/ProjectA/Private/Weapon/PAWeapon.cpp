// ProjectA, Tikhonov Gennadii, All Rights Reserved

#include "Weapon/PAWeapon.h"
#include "Weapon/WeaponConfig/BaseWeaponConfig.h"
#include "Weapon/WeaponConfig/Enum/AmmoType.h"


void APAWeapon::StartAttack()
{
	
}

void APAWeapon::StopAttack()
{
	
}

void APAWeapon::ReloadWeapon()
{
}

bool APAWeapon::CanBeReloaded()
{
	return false;
}

bool APAWeapon::TryAddClips(int32 Clips)
{
	return false;
}

UBaseWeaponConfig* APAWeapon::GetWeaponConfig() const
{
	return WeaponConfig;
}

EWeaponType APAWeapon::GetWeaponType()
{
	if (WeaponConfig)
	{
		return WeaponConfig->WeaponType;
	}
	return EWeaponType::None;
}

EAmmoType APAWeapon::GetWeaponAmmoType() const
{
	return EAmmoType::None;
}

void APAWeapon::AttachWeaponToArmedSocket(USceneComponent* OwnerComponent)
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	AttachToComponent(OwnerComponent, AttachmentRules, WeaponConfig->AttachWeaponSocket);
}

void APAWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(GetWeaponType() != EWeaponType::None)
	
}

