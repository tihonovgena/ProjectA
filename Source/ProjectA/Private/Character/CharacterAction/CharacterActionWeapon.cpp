// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/CharacterAction/CharacterActionWeapon.h"

UAnimMontage* UCharacterActionWeapon::GetWeaponTypeAnimMontage(EWeaponType WeaponType)
{
	if (WeaponTypeActions.Contains(WeaponType))
	{
		return *WeaponTypeActions.Find(WeaponType);
	}
	
	return nullptr;
	
}
