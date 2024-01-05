// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Item/Pickup/AmmoPickup.h"

#include "Interface/HealthComponentInterface.h"
#include "Interface/WeaponComponentInterface.h"

DEFINE_LOG_CATEGORY_STATIC(AmmoPickup, Log, All);

AAmmoPickup::AAmmoPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AAmmoPickup::PickUpItem(APawn* Pawn)
{
	IHealthComponentInterface* HealthComponentInterface = Cast<IHealthComponentInterface>(Pawn);
	IWeaponComponentInterface* WeaponComponentInterface = Cast<IWeaponComponentInterface>(Pawn);
	if(!HealthComponentInterface || !WeaponComponentInterface) return false;

	if (HealthComponentInterface->IsDead())
	{
		return false;
	}
	else
	{
		return WeaponComponentInterface->TryAddWeaponClips(AmmoType, Clips);
	}
	
}

void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

