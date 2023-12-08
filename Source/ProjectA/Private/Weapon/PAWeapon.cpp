// ProjectA, Tikhonov Gennadii, All Rights Reserved

#include "Weapon/PAWeapon.h"
#include "Weapon/WeaponConfig/BaseWeaponConfig.h"


void APAWeapon::StartAttack()
{
	
}

void APAWeapon::StopAttack()
{
	
}

UBaseWeaponConfig* APAWeapon::GetWeaponConfig()
{
	return WeaponConfig;
}

void APAWeapon::AttachWeaponToArmedSocket(USceneComponent* OwnerComponent)
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	AttachToComponent(OwnerComponent, AttachmentRules, WeaponConfig->AttachWeaponSocket);
}

void APAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

