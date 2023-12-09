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
	void SwitchWeapon();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void SpawnWeapons();
	USceneComponent* GetOwnerMesh() const;

	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "WeaponArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<APAWeapon>> WeaponClasses;
	
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	TObjectPtr<APAWeapon> ArmedWeapon;

private:
	APAWeapon* SpawnWeapon(TSubclassOf<APAWeapon> WeaponClass);
	void EquipWeapon(APAWeapon* Weapon);
	void AttachWeaponToArmorySocket(APAWeapon* Weapon);
	int32 GetNextWeaponIndex();

	UPROPERTY()
	TArray<APAWeapon*> Weapons;

};