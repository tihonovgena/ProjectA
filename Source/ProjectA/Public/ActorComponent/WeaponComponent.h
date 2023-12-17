// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/WeaponConfig/Enum/WeaponType.h"
#include "WeaponComponent.generated.h"

class IWeaponComponentInterface;
class UBaseWeaponConfig;
class APAWeapon;

DECLARE_LOG_CATEGORY_EXTERN(WeaponComponent, Display, All);

DECLARE_MULTICAST_DELEGATE(FOnWeaponNeedReloadSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	
	AController* GetOwnerController() const;
	EWeaponType GetEquipWeaponType();
	EWeaponType GetWeaponType() const;

	UFUNCTION()
	void StartAttack();
	
	UFUNCTION()
	void StopAttack();
	
	UFUNCTION()
	void SwitchWeapon();
	
	UFUNCTION()
	void FinishSwitchWeapon();

	UFUNCTION()
	void ReloadWeapon();

	FOnWeaponNeedReloadSignature WeaponNeedReload;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void SpawnWeapons();
	
	USceneComponent* GetOwnerMesh();
	IWeaponComponentInterface* GetOwnerWeaponInterface();

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
	void BindWeaponDelegates(APAWeapon* Weapon);
	void UnbindWeaponDelegates(APAWeapon* Weapon);
	
	UFUNCTION()
	void OnWeaponNeedReload();
	
	int32 GetNextWeaponIndex() const;

	UPROPERTY()
	TArray<APAWeapon*> Weapons;

};
