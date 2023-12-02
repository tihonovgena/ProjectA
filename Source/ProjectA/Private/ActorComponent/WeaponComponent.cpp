// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(WeaponComponent)

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	check(Weapon);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer
		(FireTimer, this, &UWeaponComponent::Shoot, FireRate, true);
	}
	
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld() || !GetOwnerMesh() || !WeaponClass) return;
	
	Weapon = GetWorld()->SpawnActor<APAWeapon>(WeaponClass);
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, AttachSocketName);
	
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
		UE_LOG(WeaponComponent, Display, TEXT("%s got the shot"), *HitResult.HitObjectHandle.GetFName().ToString());
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
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility);
	return true;
}

