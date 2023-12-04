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
	if (IsValid(Pawn))
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
	
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld() || !GetOwnerMesh() || !WeaponClass) return;
	
	Weapon = GetWorld()->SpawnActor<APAWeapon>(WeaponClass);
	if (!IsValid(Weapon)) return;
	
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, AttachWeaponSocket);
	Weapon->SetOwner(ComponentOwner);
	
}

void UWeaponComponent::StartAttack()
{
	Weapon->StartAttack();
	
}

void UWeaponComponent::StopAttack()
{
	Weapon->StopAttack();
	
}


USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!IsValid(Character)) return nullptr;
	return  Character->GetMesh();
}
