// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/AICharacter.h"

#include "ActorComponent/HealthComponent.h"

AAICharacter::AAICharacter()
{
	
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAICharacter::CanBeDetected()
{
	return !HealthComponent->IsDead();
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	SetLifeSpan(5.0f);
}

void AAICharacter::OnHealthChanged(float Health)
{
	Super::OnHealthChanged(Health);
}
