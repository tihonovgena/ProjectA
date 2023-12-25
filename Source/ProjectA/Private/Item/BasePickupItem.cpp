// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Item/BasePickupItem.h"

#include "Components/SphereComponent.h"


// Sets default values
ABasePickupItem::ABasePickupItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetSphereRadius(50.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ABasePickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickupItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Pickup");
	Destroy();
}

// Called every frame
void ABasePickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

