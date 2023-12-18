#pragma once

#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	Rifle = 1,
	Launcher = 2
};