// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Item/Pickup/HealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(HealthPickup, Log, All);

AHealthPickup::AHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AHealthPickup::PickUpItem(APawn* Pawn)
{
	UE_LOG(HealthPickup, Log, TEXT("Health picked up"));
	return true;
}

void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

