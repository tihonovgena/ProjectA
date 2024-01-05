#pragma once

#include "AmmoType.generated.h"

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	None = 0,
	Rifle = 1,
	Launcher = 2
};