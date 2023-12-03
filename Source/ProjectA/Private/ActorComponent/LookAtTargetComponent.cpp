// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/LookAtTargetComponent.h"
#include "TimerManager.h"
#include "Interface/LookAtEnemyInterface.h"
#include "Kismet/KismetMathLibrary.h"

ULookAtTargetComponent::ULookAtTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void ULookAtTargetComponent::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
}

void ULookAtTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		ComponentOwner = GetOwner();
	}
	
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer
		(UpdaterTimer, this, &ULookAtTargetComponent::LookAtTarget, UpdateFrequency, true, -1);
	}	
}

void ULookAtTargetComponent::LookAtTarget()
{
	if (IsValid(Target) && IsValid(ComponentOwner))
	{
		float YawDegrees;
		float PitchDegrees;
		CalculateAnglesToTarget(YawDegrees, PitchDegrees);
		MakeRotate(FRotator(PitchDegrees, YawDegrees,0 ));
		
	}
	
}

void ULookAtTargetComponent::CalculateAnglesToTarget(float& YawDegrees, float& PitchDegrees)
{
	const FVector TargetLocation = Target->GetActorLocation();
	const FVector OwnerLocation = ComponentOwner->GetActorLocation();
	const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
	YawDegrees = Rotator.Yaw;
	PitchDegrees= Rotator.Pitch;
	
}

void ULookAtTargetComponent::MakeRotate(FRotator Rotator)
{
	ILookAtEnemyInterface* LookAtEnemyInterface = Cast<ILookAtEnemyInterface>(ComponentOwner);
	if (LookAtEnemyInterface)
	{
		LookAtEnemyInterface->MakeRotateToTarget(Rotator);
	}
}

