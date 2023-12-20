// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/BaseGunWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Weapon/WeaponConfig/GunWeaponConfig.h"

DEFINE_LOG_CATEGORY(WeaponGun)

FTransform ABaseGunWeapon::GetShotSocketTransform()
{
	return FTransform();
}

AController* ABaseGunWeapon::GetOwnerController()
{
	if (!GetOwner()) return nullptr;
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!IsValid(Pawn)) return nullptr;
	return Pawn->GetController();
	
}

UGunWeaponConfig* ABaseGunWeapon::GetGunWeaponConfig() const
{
	return Cast<UGunWeaponConfig>(GetWeaponConfig());
}

void ABaseGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SetupWeaponAmmo();
	
}

FWeaponAmmo ABaseGunWeapon::GetWeaponAmmo() const
{
	return WeaponAmmoStruct;
}

 bool ABaseGunWeapon::GetWeaponDefaultAmmo(FWeaponAmmo& DefaultWeaponAmmo) const
{
	if (GetGunWeaponConfig())
	{
		DefaultWeaponAmmo = GetGunWeaponConfig()->DefaultWeaponAmmo;
		return true;
	}
	return false;
}

void ABaseGunWeapon::ReloadWeapon()
{
	if (CanBeReloaded())
	{
		WeaponAmmoStruct.Ammo = GetGunWeaponConfig()->DefaultWeaponAmmo.Ammo;
		WeaponAmmoStruct.Clips--;
		UE_LOG(LogTemp, Display, TEXT("Weapon realoaded"))
		
	}
}

bool ABaseGunWeapon::HasAmmo() const
{
	return WeaponAmmoStruct.Ammo > 0;
}

bool ABaseGunWeapon::HasClips() const
{
	if (AreClipsInfinity())
	{
		return true;
	}
	
	return WeaponAmmoStruct.Clips > 0;
	
}

bool ABaseGunWeapon::AreClipsInfinity() const
{
	return WeaponAmmoStruct.bInfinityClips;
}

bool ABaseGunWeapon::CanBeReloaded()
{
	return HasClips();
}

void ABaseGunWeapon::SetupWeaponAmmo()
{
	WeaponAmmoStruct = GetGunWeaponConfig()->DefaultWeaponAmmo;
}

void ABaseGunWeapon::StartAttack()
{
	if (HasAmmo())
	{
		GetWorldTimerManager().SetTimer(ShootTimer,this, &ABaseGunWeapon::MakeShot, GetGunWeaponConfig()->FireRate, true, -1);
	}
	else
	{
		NeedReload.Broadcast();
	}
}

void ABaseGunWeapon::StopAttack()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ABaseGunWeapon::Shot()
{
	
}

void ABaseGunWeapon::MakeShot()
{
	if (!HasAmmo())
	{
		StopAttack();
		NeedReload.Broadcast();
	}
	else
	{
		Shot();
		WeaponAmmoStruct.Ammo--;

		UE_LOG(LogTemp, Display, TEXT("Ammo %s"), *FString::FromInt(WeaponAmmoStruct.Ammo));
	}
	
}

void ABaseGunWeapon::MakeDamage(FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (IsValid(DamagedActor))
	{
		DamagedActor->TakeDamage(10.0f, FDamageEvent(),GetOwnerController(), this);
	}
}


