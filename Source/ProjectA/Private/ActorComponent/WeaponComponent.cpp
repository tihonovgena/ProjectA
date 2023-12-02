// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Weapon/SkeletalGun.h"

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

	StartShootTimer();
	
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld() || !GetOwnerMesh() || !WeaponClass) return;
	
	Weapon = GetWorld()->SpawnActor<APAWeapon>(WeaponClass);
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, AttachWeaponSocket);
	Weapon->SetOwner(ComponentOwner);
	
}

void UWeaponComponent::StartShootTimer()
{
	ASkeletalGun* GunWeapon = Cast<ASkeletalGun>(Weapon);
	if (!GunWeapon || !GetWorld()) return;
	
	GetWorld()->GetTimerManager().SetTimer
	(ShootTimer, GunWeapon, &ASkeletalGun::Shoot, FireRate, true);
	
}


USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;
	return  Character->GetMesh();
}