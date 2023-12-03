// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PACharacter.h"
#include "ActorComponent/HealthComponent.h"
#include "Components/CapsuleComponent.h"

APACharacter::APACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
}

void APACharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &APACharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &APACharacter::OnHealthChanged);
	
}

void APACharacter::OnDeath()
{
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void APACharacter::OnHealthChanged(float Health)
{
	
}


void APACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool APACharacter::IsMoving()
{
	return  !GetVelocity().IsNearlyZero();
}

float APACharacter::GetCharacterSpeed()
{
	return GetVelocity().Length();
}

float APACharacter::GetMovementDegreesDirection()
{
	if(!IsMoving())
	{
		return 0.0f;
	}
	const FVector MovementDirection = GetVelocity().GetSafeNormal();
	const float VectorsDotProduct = FVector::DotProduct(GetActorForwardVector(), MovementDirection);
	const float AcosDotProduct = FMath::Acos(VectorsDotProduct);
	const FVector VectorsCross = FVector::CrossProduct(GetActorForwardVector(), MovementDirection);
	const float Degrees = FMath::RadiansToDegrees(AcosDotProduct);
	return Degrees * FMath::Sign(VectorsCross.Z);
}

