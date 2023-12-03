// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LookAtTargetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULookAtTargetInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTA_API ILookAtTargetInterface
{
	GENERATED_BODY()

public:
	virtual void MakeRotateToTarget(FRotator Rotator);
};
