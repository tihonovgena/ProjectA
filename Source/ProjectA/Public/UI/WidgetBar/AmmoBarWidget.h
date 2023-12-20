// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoBarWidget.generated.h"


struct FWeaponAmmo;

UCLASS()
class PROJECTA_API UAmmoBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetWeaponAmmo(FWeaponAmmo& WeaponAmmo);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo);
};
