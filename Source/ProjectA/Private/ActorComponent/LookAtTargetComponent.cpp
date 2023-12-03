// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/LookAtTargetComponent.h"
#include "TimerManager.h"
#include "Interface/LookAtTargetInterface.h"
#include "Kismet/KismetMathLibrary.h"

ULookAtTargetComponent::ULookAtTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void ULookAtTargetComponent::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
}

FRotator ULookAtTargetComponent::GetRotatorBetweenTarget()
{
	if (IsValid(ComponentOwner) && IsValid(Target))
	{
		return ComponentOwner->GetActorRotation() - RotatorToTarget;	
	}
	
	return FRotator::ZeroRotator;
	
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
		RotatorToTarget = CalculateRotatorToTarget();
		
		if (FMath::Abs(GetRotatorBetweenTarget().Yaw) >= YawAngleToRotate)
		{
			const FRotator InterpRotatorToTarget = FMath::RInterpTo(ComponentOwner->GetActorRotation(), RotatorToTarget, UpdateFrequency, InterpRotationSpeed);
			MakeRotate(InterpRotatorToTarget);
		}
	}
	else
	{
		RotatorToTarget = FRotator::ZeroRotator;
	}
	
}

FRotator ULookAtTargetComponent::CalculateRotatorToTarget()
{
	const FVector TargetLocation = Target->GetActorLocation();
	const FVector OwnerLocation = ComponentOwner->GetActorLocation();
	const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
	return FRotator(Rotator.Pitch, Rotator.Yaw,0 );
}

void ULookAtTargetComponent::MakeRotate(FRotator Rotator)
{
	ILookAtTargetInterface* LookAtEnemyInterface = Cast<ILookAtTargetInterface>(ComponentOwner);
	if (LookAtEnemyInterface)
	{
		LookAtEnemyInterface->MakeRotateToTarget(Rotator);
	}
}

