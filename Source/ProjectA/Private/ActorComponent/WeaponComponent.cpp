// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

#define COLLISION_WEAPON ECC_GameTraceChannel1

DEFINE_LOG_CATEGORY(WeaponComponent);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

AController* UWeaponComponent::GetOwnerController()
{
	const APawn* Pawn = Cast<APawn>(ComponentOwner);
	if (Pawn)
	{
		return Pawn->GetController();
	}
	else
	{
		return nullptr;
	}
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	ComponentOwner = GetOwner();
	check(ComponentOwner)
	
	SpawnWeapon();
	check(Weapon);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer
		(ShootTimer, this, &UWeaponComponent::Shoot, FireRate, true);
	}
	
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld() || !GetOwnerMesh() || !WeaponClass) return;
	
	Weapon = GetWorld()->SpawnActor<APAWeapon>(WeaponClass);
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, AttachWeaponSocket);
	
}

USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;
	return  Character->GetMesh();
}

void UWeaponComponent::Shoot()
{
	MakeShot();
	
}

void UWeaponComponent::MakeShot()
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
		
		AActor* HitActor = HitResult.HitObjectHandle.FetchActor();
		if (HitActor)
		{
			HitActor->TakeDamage(10.0f, FDamageEvent{},GetOwnerController(), ComponentOwner);
			UE_LOG(WeaponComponent, Display, TEXT("%s got the shot"), *HitActor->GetName());
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 2.0f, 0, 2.0f);
	}
	
}

bool UWeaponComponent::GetTraceData(FVector& StartTrace, FVector& EndTrace)
{
	if(!Weapon) return false;
	
	StartTrace = Weapon->GetShotSocketTransform().GetLocation();
	const FVector TraceDirection = Weapon->GetShotSocketTransform().GetRotation().GetForwardVector();
	EndTrace = StartTrace + (TraceDirection * ShotDistance);
	return true;
	
}

bool UWeaponComponent::MakeShotTrace(FHitResult& HitResult, FVector& StartTrace, FVector& EndTrace)
{
	if(!GetWorld()) return false;
	GetTraceData(StartTrace, EndTrace);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, COLLISION_WEAPON);
	return true;
}

