// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAWeapon.generated.h"

class UBaseWeaponConfig;

UCLASS(Abstract)
class PROJECTA_API APAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	APAWeapon();
	virtual void StartAttack();
	virtual void StopAttack();
	virtual void SetWeaponConfig(UBaseWeaponConfig* NewWeaponConfig);

protected:
	virtual void BeginPlay() override;
};
