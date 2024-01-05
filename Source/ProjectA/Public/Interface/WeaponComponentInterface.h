// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponComponentInterface.generated.h"

enum class EAmmoType : uint8;
struct FWeaponAmmo;
// This class does not need to be modified.
UINTERFACE()
class UWeaponComponentInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECTA_API IWeaponComponentInterface
{
	GENERATED_BODY()

public:
	virtual USceneComponent* GetWeaponComponentOwnerMesh();
	virtual bool CanContinueAttack();
	virtual bool GetWeaponAmmo(FWeaponAmmo& WeaponAmmo);
	virtual bool GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo);
	virtual bool TryAddWeaponClips(EAmmoType AmmoType, int32 Clips);
};
