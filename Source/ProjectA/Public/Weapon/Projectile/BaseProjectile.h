// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Damage/PhysicalDamageType.h"
#include "BaseProjectile.generated.h"

class UPhysicalDamageType;
class UPADamageType;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class PROJECTA_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABaseProjectile();

	void SetMoveDirection(const FVector& Direction);

protected:
	virtual void BeginPlay() override;
	virtual void MakeDamage();

private:
	AController* GetOwnerController();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "LifeSpan", meta = (ClampMin = "0.0"))
	float LifeSpan = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (ClampMin = "0.0"))
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (ClampMin = "0.0"))
	float DamageRadius = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool bDoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UPADamageType> DamageTypeClass = UPhysicalDamageType::StaticClass();
		
	FVector MoveDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
