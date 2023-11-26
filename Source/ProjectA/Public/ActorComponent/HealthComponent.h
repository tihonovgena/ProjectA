// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HealthComponent, Display, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category="Health")
	float GetMaxHealth() const;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AActor* ComponentOwner;
	
	UPROPERTY()
	float Health = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth = 100.f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,AController* InstigatedBy, AActor* DamageCauser);
};
