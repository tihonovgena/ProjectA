// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyDetectorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyDetectorInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTA_API IEnemyDetectorInterface
{
	GENERATED_BODY()

public:
	
	virtual bool CanBeDetected();
};

inline bool IEnemyDetectorInterface::CanBeDetected()
{
	return false;
}
