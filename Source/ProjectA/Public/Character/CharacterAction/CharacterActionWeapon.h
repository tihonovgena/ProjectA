// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterAction.h"
#include "Weapon/WeaponConfig/Enum/WeaponType.h"
#include "CharacterActionWeapon.generated.h"

UCLASS()
class PROJECTA_API UCharacterActionWeapon : public UBaseCharacterAction
{
	GENERATED_BODY()

public:
	UAnimMontage* GetWeaponTypeAnimMontage(EWeaponType WeaponType);
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TMap<EWeaponType, UAnimMontage*> WeaponTypeActions;
};
