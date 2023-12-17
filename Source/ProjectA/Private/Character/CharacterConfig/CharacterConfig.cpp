// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/CharacterConfig/CharacterConfig.h"
#include "Character/CharacterAction/CharacterActionWeapon.h"

UAnimMontage* UCharacterConfig::GetSwitchWeaponAnimMontage(EWeaponType WeaponType)
{
	if (WeaponSwitch)
	{
		return WeaponSwitch->GetWeaponTypeAnimMontage(WeaponType);
	}

	return nullptr;
	
}

UAnimMontage* UCharacterConfig::GetReloadWeaponAnimMontage(EWeaponType WeaponType)
{
	if (WeaponReload)
	{
		return WeaponReload->GetWeaponTypeAnimMontage(WeaponType);
	}

	return nullptr;
	
}
