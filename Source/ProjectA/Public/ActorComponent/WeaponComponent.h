// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(WeaponComponent, Display, All)

class APAWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<APAWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName AttachSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float FireRate = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float ShotDistance = 1000.0f;

	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	APAWeapon* Weapon;
	
	virtual void SpawnWeapon();
	virtual USceneComponent* GetOwnerMesh() const;
	virtual void Shoot();
	virtual void MakeShot();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerHandle FireTimer;
	
};
