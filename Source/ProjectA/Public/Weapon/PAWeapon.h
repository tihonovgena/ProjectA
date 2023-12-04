// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAWeapon.generated.h"

UCLASS(Abstract)
class PROJECTA_API APAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	APAWeapon();
	virtual void StartAttack();
	virtual void StopAttack();

protected:
	virtual void BeginPlay() override;
};
