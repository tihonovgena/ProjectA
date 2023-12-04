// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"

bool ARifleWeapon::GetTraceData(FVector& StartTrace, FVector& EndTrace)
{
	StartTrace = GetShotSocketTransform().GetLocation();
	const FVector TraceDirection = GetShotSocketTransform().GetRotation().GetForwardVector();
	EndTrace = StartTrace + (TraceDirection * ShotDistance);
	return true;
	
}

void ARifleWeapon::MakeShot()
{
	if(!GetWorld()) return;

	FVector StartTrace;
	FVector EndTrace;
	FHitResult HitResult;
	MakeShotTrace(HitResult, StartTrace, EndTrace);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), StartTrace, HitResult.ImpactPoint, FColor::Red, false, 2.0f, 0, 2.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 12, FColor::Red, false, 5.0f,0, 1.0f);

		MakeDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 2.0f, 0, 2.0f);
	}
}

bool ARifleWeapon::MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace)
{
	if(!GetWorld()) return false;
	GetTraceData(StartTrace, EndTrace);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, COLLISION_WEAPON);
	return true;
}
