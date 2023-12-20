// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"
#include "Weapon/PAWeapon.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Interface/WeaponComponentInterface.h"
#include "Weapon/BaseGunWeapon.h"

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

bool UWeaponComponent::GetWeaponAmmo(FWeaponAmmo& WeaponAmmo) const
{
	const ABaseGunWeapon* GunWeapon = Cast<ABaseGunWeapon>(ArmedWeapon);
	if (IsValid(GunWeapon))
	{
		WeaponAmmo = GunWeapon->GetWeaponAmmo();
		return true;
	}
	return false;
}

bool UWeaponComponent::GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo) const
{
	const ABaseGunWeapon* GunWeapon = Cast<ABaseGunWeapon>(ArmedWeapon);
	if (IsValid(GunWeapon))
	{
		return GunWeapon->GetWeaponDefaultAmmo(WeaponAmmo);
	}
	return false;
}

EWeaponType UWeaponComponent::GetEquipWeaponType() const
{
	if (Weapons.IsEmpty() || !Weapons[GetNextWeaponIndex()]) return EWeaponType::None;
	return Weapons[GetNextWeaponIndex()]->GetWeaponType();
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

void UWeaponComponent::EquipWeapon(APAWeapon* Weapon)
{
	if (IsValid(Weapon))
	{
		if (IsValid(ArmedWeapon))
		{
			ArmedWeapon->StopAttack();
			AttachWeaponToArmorySocket(ArmedWeapon);
			UnbindWeaponDelegates(ArmedWeapon);
		}
		ArmedWeapon = Weapon;
		ArmedWeapon->AttachWeaponToArmedSocket(GetOwnerMesh());
		BindWeaponDelegates(ArmedWeapon);
	}
}

void UWeaponComponent::AttachWeaponToArmorySocket(APAWeapon* Weapon)
{
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, WeaponArmorySocketName);
}

inline void UWeaponComponent::BindWeaponDelegates(APAWeapon* Weapon)
{
	Weapon->NeedReload.AddUObject(this, &UWeaponComponent::OnWeaponNeedReload);
}

void UWeaponComponent::UnbindWeaponDelegates(APAWeapon* Weapon)
{
	Weapon->NeedReload.Clear();
}

void UWeaponComponent::OnWeaponNeedReload()
{
	if (IsValid(ArmedWeapon) && ArmedWeapon->CanBeReloaded())
	{
		WeaponNeedReload.Broadcast();
	}
	
}

int32 UWeaponComponent::GetNextWeaponIndex() const
{
	int32 ArmedWeaponIndex = 0;
	Weapons.Find(ArmedWeapon, ArmedWeaponIndex);
	return Weapons.IsValidIndex(ArmedWeaponIndex + 1) ? ArmedWeaponIndex + 1 : 0;
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

EWeaponType UWeaponComponent::GetWeaponType() const
{
	if (ArmedWeapon)
	{
		return ArmedWeapon->GetWeaponType();
	}
	return EWeaponType::None;
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
	IWeaponComponentInterface* WeaponComponentInterface = GetOwnerWeaponInterface();
	if (WeaponComponentInterface && WeaponComponentInterface->CanContinueAttack())
	{
		StartAttack();
	}
	
}

void UWeaponComponent::ReloadWeapon()
{
	if (IsValid(ArmedWeapon))
	{
		ArmedWeapon->ReloadWeapon();
	}
}

USceneComponent* UWeaponComponent::GetOwnerMesh()
{
	IWeaponComponentInterface* WeaponComponentInterface = GetOwnerWeaponInterface();
	if (WeaponComponentInterface)
	{
		return WeaponComponentInterface->GetWeaponComponentOwnerMesh();
	}
	else
	{
		return nullptr;
	}
	
}

IWeaponComponentInterface* UWeaponComponent::GetOwnerWeaponInterface()
{
	if (!GetOwner()) return nullptr;
	IWeaponComponentInterface* WeaponComponentInterface = Cast<IWeaponComponentInterface>(GetOwner());
	if (WeaponComponentInterface)
	{
		return WeaponComponentInterface;
	}
	return nullptr;
}
