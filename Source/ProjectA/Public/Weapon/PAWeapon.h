// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponConfig/Enum/WeaponType.h"
#include "PAWeapon.generated.h"

class UBaseWeaponAction;
class UBaseWeaponConfig;

DECLARE_MULTICAST_DELEGATE(FOnNeedReloadSignature);

UCLASS(Abstract)
class PROJECTA_API APAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void StartAttack();
	virtual void StopAttack();
	virtual void ReloadWeapon();
	virtual bool CanBeReloaded();
	
	void AttachWeaponToArmedSocket(USceneComponent* OwnerComponent);
	
	UBaseWeaponConfig* GetWeaponConfig() const;
	EWeaponType GetWeaponType();

	FOnNeedReloadSignature NeedReload;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponConfig")
	const TObjectPtr<UBaseWeaponConfig> WeaponConfig;
	
};
