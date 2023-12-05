// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseLauncherWeapon.h"
#include "SkeletonLauncherWeapon.generated.h"

UCLASS()
class PROJECTA_API ASkeletonLauncherWeapon : public ABaseLauncherWeapon
{
	GENERATED_BODY()

public:
	ASkeletonLauncherWeapon();
	virtual FTransform GetShotSocketTransform() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
};
