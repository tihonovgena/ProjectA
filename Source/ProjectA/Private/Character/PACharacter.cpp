// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PACharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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
	if (EnableRotateToDirection)
	{
		RotateMeshToDirection();
	}

}

void APACharacter::RotateMeshToDirection() const
{
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	const FVector Velocity = FVector(GetVelocity().X, GetVelocity().Y, 0.0f);
	if (Velocity.IsNearlyZero() || !CharacterMesh)
	{
		return;
	}
	const FVector MovementDirection = GetVelocity().GetSafeNormal();
	const float YawRotation = FMath::RadiansToDegrees(FMath::Atan2(-MovementDirection.X,MovementDirection.Y));
	const FRotator TargetRotation = FRotator(0.0f, YawRotation, 0.0f);
	const FRotator CurrentRotation = CharacterMesh->GetComponentRotation();
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->DeltaTimeSeconds,RotationInterpSpeed);
	CharacterMesh->SetWorldRotation(NewRotation);
}

