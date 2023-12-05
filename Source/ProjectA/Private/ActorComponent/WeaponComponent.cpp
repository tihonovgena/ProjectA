// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Weapon/WeaponConfig/BaseWeaponConfig.h"

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
	
	if (bSpawnDefaultWeapon)
	{
		SpawnDefaultWeapon();
	}
	
}

void UWeaponComponent::SpawnDefaultWeapon()
{
	SpawnWeapon(DefaultWeaponConfig);
}

void UWeaponComponent::SpawnWeapon(UBaseWeaponConfig* WeaponConfig)
{
	if (!GetWorld() || !IsValid(WeaponConfig) || !IsValid(GetOwnerMesh()) || !IsValid(WeaponConfig->WeaponClass))
	{
		return;
	}

	Weapon = GetWorld()->SpawnActorDeferred<APAWeapon>(WeaponConfig->WeaponClass, FTransform());
	if (Weapon)
	{
		Weapon->SetWeaponConfig(WeaponConfig);
		const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, WeaponConfig->AttachWeaponSocket);
		Weapon->SetOwner(ComponentOwner);
		Weapon->FinishSpawning(FTransform());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn weapon of class %s"), *WeaponConfig->WeaponClass->GetName());
	}
}

void UWeaponComponent::StartAttack()
{
	if (IsValid(Weapon))
	{
		Weapon->StartAttack();
	}
}

void UWeaponComponent::StopAttack()
{
	if (IsValid(Weapon))
	{
		Weapon->StopAttack();
	}
}


USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!IsValid(Character)) return nullptr;
	return  Character->GetMesh();
}
