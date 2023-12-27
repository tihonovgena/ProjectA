// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Item/BasePickupItem.h"

#include "Components/SphereComponent.h"


// Sets default values
ABasePickupItem::ABasePickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(50.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ABasePickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickupItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APawn* Pawn = Cast<APawn>(OtherActor);
	if(PickUpItem(Pawn))
	{
		ItemWasTaken();
		FTimerHandle RespawnTimer;
		GetWorldTimerManager().SetTimer(RespawnTimer, this, &ABasePickupItem::RespawnItem, RespawnTime);
	}
}

// Called every frame
void ABasePickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickupItem::ItemWasTaken()
{
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent->SetVisibility(false, true);
}

void ABasePickupItem::RespawnItem()
{
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RootComponent->SetVisibility(true, true);
}

bool ABasePickupItem::PickUpItem(APawn* Pawn)
{
	return false;
}

