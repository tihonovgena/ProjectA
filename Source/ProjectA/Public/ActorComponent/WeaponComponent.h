// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(WeaponComponent, Display, All);

class APAWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	AController* GetOwnerController();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AActor* ComponentOwner;

	
#pragma region Weapon
public:
	void StartAttack();
	void StopAttack();
	
protected:
	virtual void SpawnWeapon();
	virtual USceneComponent* GetOwnerMesh() const;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<APAWeapon> WeaponClass;
	
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	TObjectPtr<APAWeapon> Weapon;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName AttachWeaponSocket;
	
#pragma endregion 
	
};