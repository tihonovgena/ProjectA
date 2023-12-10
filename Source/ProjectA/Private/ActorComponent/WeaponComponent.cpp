// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Interface/WeaponComponentInterface.h"

DEFINE_LOG_CATEGORY(WeaponComponent);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

AController* UWeaponComponent::GetOwnerController() const
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

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (const auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy(); 
	}
	Weapons.Empty();
	ArmedWeapon = nullptr;
	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapons()
{
	for (const auto WeaponClass : WeaponClasses)
	{
		if (WeaponClass)
		{
			APAWeapon* Weapon = SpawnWeapon(WeaponClass);
			Weapons.Add(Weapon);
		}
	}
	
	EquipWeapon(Weapons[0]);
}

APAWeapon* UWeaponComponent::SpawnWeapon(TSubclassOf<APAWeapon> WeaponClass) const
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

void UWeaponComponent::EquipWeapon(APAWeapon* Weapon)
{
	if (IsValid(Weapon))
	{
		if (IsValid(ArmedWeapon))
		{
			ArmedWeapon->StopAttack();
			AttachWeaponToArmorySocket(ArmedWeapon);
		}
		ArmedWeapon = Weapon;
		Weapon->AttachWeaponToArmedSocket(GetOwnerMesh());
	}
}

void UWeaponComponent::AttachWeaponToArmorySocket(APAWeapon* Weapon) const
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, WeaponArmorySocketName);
}

int32 UWeaponComponent::GetNextWeaponIndex() const
{
	int32 ArmedWeaponIndex = 0;
	Weapons.Find(ArmedWeapon, ArmedWeaponIndex);
	return Weapons.IsValidIndex(ArmedWeaponIndex + 1) ? ArmedWeaponIndex + 1 : 0;
}

void UWeaponComponent::StartAttack() const
{
	if (IsValid(ArmedWeapon))
	{
		ArmedWeapon->StartAttack();
	}
}

void UWeaponComponent::StopAttack() const
{
	if (IsValid(ArmedWeapon))
	{
		ArmedWeapon->StopAttack();
	}
}

UAnimMontage* UWeaponComponent::GetEquipWeaponAnimMontage()
{
	if (Weapons.IsEmpty()) return nullptr;
	return Weapons[GetNextWeaponIndex()]->GetEquipWeaponAnimMontage();
}

void UWeaponComponent::SwitchWeapon()
{
	if (Weapons.Num() > 1)
	{
		EquipWeapon(Weapons[GetNextWeaponIndex()]);
	}
}

void UWeaponComponent::FinishSwitchWeapon()
{
	
}

USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	IWeaponComponentInterface* WeaponComponentInterface = Cast<IWeaponComponentInterface>(GetOwner());
	if (WeaponComponentInterface)
	{
		return WeaponComponentInterface->GetWeaponComponentOwnerMesh();
	}
	else
	{
		return nullptr;
	}
	
}
