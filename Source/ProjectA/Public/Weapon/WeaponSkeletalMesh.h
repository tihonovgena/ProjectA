// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PAWeapon.h"
#include "WeaponSkeletalMesh.generated.h"

class USkeletalMeshComponent;

UCLASS()
class PROJECTA_API AWeaponSkeletalMesh : public APAWeapon
{
	GENERATED_BODY()
	
public:
	AWeaponSkeletalMesh();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Mesh")
	USkeletalMeshComponent* WeaponMesh;
};
