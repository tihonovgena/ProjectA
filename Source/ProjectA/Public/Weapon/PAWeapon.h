// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PAWeapon.generated.h"

class UBaseWeaponAction;
class UBaseWeaponConfig;

UCLASS(Abstract)
class PROJECTA_API APAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void StartAttack();
	virtual void StopAttack();
	
	UBaseWeaponConfig* GetWeaponConfig();
	UAnimMontage* GetEquipWeaponAnimMontage();
	
	void AttachWeaponToArmedSocket(USceneComponent* OwnerComponent);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponConfig")
	const TObjectPtr<UBaseWeaponConfig> WeaponConfig;
	
};
