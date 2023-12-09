// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

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
	
	SpawnWeapons();
	
}

void UWeaponComponent::SpawnWeapons()
{
	for (const auto WeaponClass : WeaponClasses)
	{
		if (SpawnWeapon(WeaponClass))
		{
			Weapons.Add(SpawnWeapon(WeaponClass));
		}
	}
	
	EquipWeaponIndex(ArmedWeaponIndex);
}

APAWeapon* UWeaponComponent::SpawnWeapon(TSubclassOf<APAWeapon> WeaponClass)
{
	if (!GetWorld() || !IsValid(WeaponClass) || !IsValid(GetOwnerMesh()))
	{
		return nullptr;
	}

	APAWeapon* Weapon = GetWorld()->SpawnActorDeferred<APAWeapon>(WeaponClass, FTransform());
	if (Weapon)
	{
		Weapon->SetOwner(ComponentOwner);
		AttachWeaponToArmorySocket(Weapon);
		Weapon->FinishSpawning(FTransform());
		return Weapon;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn weapon of class %s"), *WeaponClass->GetName());
		return nullptr;
	}
}

void UWeaponComponent::EquipWeaponIndex(int32 WeaponIndex)
{
	if (Weapons.IsValidIndex(WeaponIndex) && IsValid(Weapons[WeaponIndex]))
	{
		if (IsValid(ArmedWeapon))
		{
			AttachWeaponToArmorySocket(ArmedWeapon);
		}
		ArmedWeapon = Weapons[WeaponIndex];
		Weapons[WeaponIndex]->AttachWeaponToArmedSocket(GetOwnerMesh());
		ArmedWeaponIndex = WeaponIndex;
	}
}

void UWeaponComponent::AttachWeaponToArmorySocket(APAWeapon* Weapon)
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, WeaponArmorySocketName);
}

void UWeaponComponent::StartAttack()
{
	if (IsValid(ArmedWeapon))
	{
		ArmedWeapon->StartAttack();
	}
}

void UWeaponComponent::StopAttack()
{
	if (IsValid(ArmedWeapon))
	{
		ArmedWeapon->StopAttack();
	}
}

void UWeaponComponent::SwitchWeapon()
{
	if (Weapons.Num() > 1)
	{
		EquipWeaponIndex(Weapons.IsValidIndex(ArmedWeaponIndex + 1) ? ArmedWeaponIndex + 1 : 0);
	}
}


USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!IsValid(Character)) return nullptr;
	return  Character->GetMesh();
}
