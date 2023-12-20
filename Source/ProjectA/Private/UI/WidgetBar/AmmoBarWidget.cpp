// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "UI/WidgetBar/AmmoBarWidget.h"

#include "Interface/WeaponComponentInterface.h"

bool UAmmoBarWidget::GetWeaponAmmo(FWeaponAmmo& WeaponAmmo)
{
	IWeaponComponentInterface* WeaponComponentInterface = Cast<IWeaponComponentInterface>(GetOwningPlayerPawn());
	if (WeaponComponentInterface)
	{
		return WeaponComponentInterface->GetWeaponAmmo(WeaponAmmo);
	}
	return false;
}

bool UAmmoBarWidget::GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo)
{
	IWeaponComponentInterface* WeaponComponentInterface = Cast<IWeaponComponentInterface>(GetOwningPlayerPawn());
	if (WeaponComponentInterface)
	{
		return WeaponComponentInterface->GetWeaponDefaultAmmo(WeaponAmmo);
	}
	return false;
}
