// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/HealthComponent.h"
#include "Gameplay/Damage/PADamageType.h"

DEFINE_LOG_CATEGORY(HealthComponent)

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

bool UHealthComponent::IsDead()
{
	return Health <= 0.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetNewHealth(MaxHealth);
	
	ComponentOwner = GetOwner();
	check(ComponentOwner);
	ComponentOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	
}

void UHealthComponent::SetNewHealth(const float NewHealth)
{
	Health = NewHealth;
	OnHealthChanged.Broadcast(Health);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                       AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead() || Damage <= 0.0f)
	{
		return;
	}

	const float NewHealth = FMath::Clamp(Health - Damage, 0.0, MaxHealth);
	SetNewHealth(NewHealth);
	
	UE_LOG(HealthComponent, Display, TEXT("%s take %f damage"), *ComponentOwner->GetName(), Damage)

	if (DamageType && DamageType->IsA<UPADamageType>())
	{
		switch (Cast<UPADamageType>(DamageType)->GetDamageType())
		{
		case EDamageType::Physical:
			UE_LOG(HealthComponent, Display, TEXT("Physical"))
			break;
			
		case EDamageType::Fire:
			UE_LOG(HealthComponent, Display, TEXT("Fire"))
			break;

		case EDamageType::Poison:
			UE_LOG(HealthComponent, Display, TEXT("Poison"))
			break;
		
		default: ;
		}
	}

	if (IsDead())
	{
		UE_LOG(HealthComponent, Display, TEXT("Player %s is dead"), *ComponentOwner->GetName());
		OnDeath.Broadcast();
	}
}


