// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PACharacter.h"

#include "Components/CapsuleComponent.h"

APACharacter::APACharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APACharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APACharacter::OnDeath()
{
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}


// Called every frame
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

