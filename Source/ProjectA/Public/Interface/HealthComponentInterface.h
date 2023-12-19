// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthComponentInterface.generated.h"

UINTERFACE()
class UHealthComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTA_API IHealthComponentInterface
{
	GENERATED_BODY()

public:
	virtual float GetHealthPercent();
};
