// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HealthComponent, Display, All);

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float Health)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	
	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;
	
private:
	UPROPERTY()
	AActor* ComponentOwner;

protected:
	virtual void BeginPlay() override;

#pragma region HealthGeneral
public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead();

private:
	float Health = 0.0f;

	void SetNewHealth(const float NewHealth);
	
	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.f;

#pragma endregion 

#pragma region AutoHeal
private:
	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal")
	bool bEnableAutoHeal = true;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (ClampMin = "0.0", EditCondition = "bEnableAutoHeal"))
	float AutoHealAmount = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (ClampMin = "0.0", EditCondition = "bEnableAutoHeal"))
	float AutoHealFrequency = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (ClampMin = "0.0", EditCondition = "bEnableAutoHeal"))
	float AutoHealDelayStart = 2.f;
	
	FTimerHandle AutoHealTimer;

	void StartAutoHealTimer();
	void StopAutoHealTimer();
	void StartAutoHeal();

#pragma endregion

#pragma region Damage
private:
	UFUNCTION()
	void OnTakeAnyDamage
	(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);

#pragma endregion
	
};
