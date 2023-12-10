// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponComponentInterface.generated.h"

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
};
