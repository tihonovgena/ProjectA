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

	//Temporary, moved to weapon asset
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float FireRate = 0.5f;

	AActor* ComponentOwner;

	
#pragma region Weapon
protected:
	virtual void SpawnWeapon();
	virtual USceneComponent* GetOwnerMesh() const;
	void StartShootTimer();

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<APAWeapon> WeaponClass;
	
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	APAWeapon* Weapon;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName AttachWeaponSocket;
	
#pragma endregion 

private:
	FTimerHandle ShootTimer;
	
};