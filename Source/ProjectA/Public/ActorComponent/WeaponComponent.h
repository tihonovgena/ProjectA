// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UBaseWeaponConfig;
class APAWeapon;

DECLARE_LOG_CATEGORY_EXTERN(WeaponComponent, Display, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	
	AController* GetOwnerController();
	void StartAttack();
	void StopAttack();
	
protected:
	virtual void BeginPlay() override;
	void SpawnDefaultWeapon();
	USceneComponent* GetOwnerMesh() const;

	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool bSpawnDefaultWeapon = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<UBaseWeaponConfig> DefaultWeaponConfig;
	
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	TObjectPtr<APAWeapon> Weapon;

private:
	void SpawnWeapon(UBaseWeaponConfig* WeaponConfig);

};