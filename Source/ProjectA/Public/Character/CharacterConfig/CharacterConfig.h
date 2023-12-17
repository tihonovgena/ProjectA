// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapon/WeaponConfig/Enum/WeaponType.h"
#include "CharacterConfig.generated.h"


class UCharacterActionWeapon;
class UBaseCharacterAction;

UCLASS()
class PROJECTA_API UCharacterConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UAnimMontage* GetSwitchWeaponAnimMontage(EWeaponType WeaponType);
	UAnimMontage* GetReloadWeaponAnimMontage(EWeaponType WeaponType);
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation | Weapon")
	TObjectPtr<UCharacterActionWeapon> WeaponSwitch;

	UPROPERTY(EditDefaultsOnly, Category = "Animation | Weapon")
	TObjectPtr<UCharacterActionWeapon> WeaponReload;
	
};
