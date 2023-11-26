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

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	ComponentOwner = GetOwner();
	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	
	const FString OwnerName = ComponentOwner->GetName();
	UE_LOG(HealthComponent, Display, TEXT("%s take %f damage"), *OwnerName, Damage)

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
}


