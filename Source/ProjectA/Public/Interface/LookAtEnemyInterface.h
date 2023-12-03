// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LookAtEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULookAtEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTA_API ILookAtEnemyInterface
{
	GENERATED_BODY()

public:
	virtual void MakeRotateToTarget(FRotator Rotator);
};
