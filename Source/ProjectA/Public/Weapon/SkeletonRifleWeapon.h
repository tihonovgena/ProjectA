// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseRifleWeapon.h"
#include "SkeletonRifleWeapon.generated.h"

UCLASS()
class PROJECTA_API ASkeletonRifleWeapon : public ABaseRifleWeapon
{
	GENERATED_BODY()

public:
	ASkeletonRifleWeapon();
	virtual FTransform GetShotSocketTransform() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
};
