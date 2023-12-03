// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/EnemyDetectorComponent.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "Interface/EnemyDetectorInterface.h"
#include "Kismet/KismetMathLibrary.h"

UEnemyDetectorComponent::UEnemyDetectorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

APawn* UEnemyDetectorComponent::GetNearestEnemy()
{
	return CurrentEnemy;
}

APawn* UEnemyDetectorComponent::GetComponentOwnerPawn()
{
	if (IsValid(ComponentOwner))
	{
		return Cast<APawn>(ComponentOwner);
	}
	
	return nullptr;
	
}

void UEnemyDetectorComponent::SetDetectionRadius(float Radius)
{
	if (Radius < 0.0f)
	{
		DetectionRadius = 0.f;
	}
	else
	{
		DetectionRadius = Radius;
	}
}

void UEnemyDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		ComponentOwner = GetOwner();
		StartDetectorEnemyTimer();
	}
}

TArray<APawn*> UEnemyDetectorComponent::GetEnemies()
{
	TArray<APawn*> Pawns;
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		if (GetComponentOwnerPawn() != *It && CanBeDetected(*It))
		{
			Pawns.Add(*It);
		}
	}
	
	// Return pawn without team filter, should be changed in the future
	return Pawns;
	
}

void UEnemyDetectorComponent::StartDetectorEnemyTimer()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer
	(UpdaterTimer, this, &UEnemyDetectorComponent::UpdateNearestEnemy, UpdateFrequency, true, -1);
}

void UEnemyDetectorComponent::UpdateNearestEnemy()
{
	SetNewEnemy(FindNearestEnemy());
}

APawn* UEnemyDetectorComponent::FindNearestEnemy()
{
	if(!IsValid(ComponentOwner)) return nullptr;
	
	APawn* NearestEnemy = nullptr;
	float Distance = 0.0f;
	
	for (const auto& Enemy : GetEnemies())
	{
		if (IsNearerThanThreshold(Distance, Enemy))
		{
			NearestEnemy = Enemy;
		}
	}
	
	return NearestEnemy;
	
}

void UEnemyDetectorComponent::SetNewEnemy(APawn* NewEnemy)
{
	if(!IsValid(NewEnemy))
	{
		if (IsValid(CurrentEnemy))
		{
			CurrentEnemy = nullptr;
			OnChangedNearestEnemy.Broadcast(CurrentEnemy);
		}
		
	}else if (!IsValid(CurrentEnemy) || CurrentEnemy != NewEnemy)
	{
		CurrentEnemy = NewEnemy;
		OnChangedNearestEnemy.Broadcast(CurrentEnemy);
	}
	
}

bool UEnemyDetectorComponent::CanBeDetected(APawn* Enemy)
{
	if(!IsValid(Enemy))return false;
	
	IEnemyDetectorInterface* EnemyInterface = Cast<IEnemyDetectorInterface>(Enemy);
	if (EnemyInterface)
	{
		return EnemyInterface->CanBeDetected();
	}
	else
	{
		return false;
	}
	
}

bool UEnemyDetectorComponent::IsNearerThanThreshold(float& Threshold,const APawn* Enemy)
{
	// Returns true if Enemy is nearer to Owner than threshold and setup new threshold and distance in detection range
	const float Distance = UKismetMathLibrary::Vector_Distance(ComponentOwner->GetActorLocation(), Enemy->GetActorLocation());
	if(DistanceInDetectionRange(Distance))
	{
		if(Threshold == 0.0f || Distance < Threshold)
		{
			Threshold = Distance;
			return true;
		}
	}
	
	return false;

}

bool UEnemyDetectorComponent::DistanceInDetectionRange(const float Distance) const
{
	return  Distance >= 0.0f && Distance <= DetectionRadius;
}

