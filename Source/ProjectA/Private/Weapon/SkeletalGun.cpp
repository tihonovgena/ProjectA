// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/SkeletalGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY(WeaponGun)

ASkeletalGun::ASkeletalGun()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	if (WeaponMesh)
	{
		SetRootComponent(WeaponMesh);
	}
}

FTransform ASkeletalGun::GetShotSocketTransform()
{
	return WeaponMesh->GetSocketTransform(ShotSocketName);
}

AController* ASkeletalGun::GetOwnerController()
{
	if (!GetOwner()) return nullptr;
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn)) return nullptr;
	return Pawn->GetController();
	
}

void ASkeletalGun::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
}

void ASkeletalGun::StartAttack()
{
	GetWorldTimerManager().SetTimer
	(ShootTimer,this, &ASkeletalGun::MakeShot, FireRate, true, -1);
}

void ASkeletalGun::StopAttack()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ASkeletalGun::MakeShot()
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

void ASkeletalGun::MakeDamage(FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (IsValid(DamagedActor))
	{
		DamagedActor->TakeDamage(10.0f, FDamageEvent(),GetOwnerController(), this);
	}
}

bool ASkeletalGun::GetTraceData(FVector& StartTrace, FVector& EndTrace)
{
	StartTrace = GetShotSocketTransform().GetLocation();
	const FVector TraceDirection = GetShotSocketTransform().GetRotation().GetForwardVector();
	EndTrace = StartTrace + (TraceDirection * ShotDistance);
	return true;
	
}

bool ASkeletalGun::MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace)
{
	if(!GetWorld()) return false;
	GetTraceData(StartTrace, EndTrace);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, COLLISION_WEAPON);
	return true;
}
