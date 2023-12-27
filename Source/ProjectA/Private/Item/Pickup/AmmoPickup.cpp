// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Item/Pickup/AmmoPickup.h"

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
	UE_LOG(AmmoPickup, Log, TEXT("Ammo picked up"));
	return true;
}

void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

