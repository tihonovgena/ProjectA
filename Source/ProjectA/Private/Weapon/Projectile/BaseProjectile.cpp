// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/Projectile/BaseProjectile.h"

#include "Components/SphereComponent.h"


ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(50.f);
	
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}
