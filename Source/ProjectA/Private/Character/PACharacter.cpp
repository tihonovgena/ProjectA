// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PACharacter.h"

// Sets default values
APACharacter::APACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APACharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

