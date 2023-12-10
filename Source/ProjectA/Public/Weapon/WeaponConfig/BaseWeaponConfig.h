// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseWeaponConfig.generated.h"

class APAWeapon;

UCLASS(Abstract, Const)
class PROJECTA_API UBaseWeaponConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	FName AttachWeaponSocket = "WeaponSocketR";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<APAWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> EquipWeaponAnimMontage; 
	
};
