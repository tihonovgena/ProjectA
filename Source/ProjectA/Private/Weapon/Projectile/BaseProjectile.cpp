// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/Projectile/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(50.f);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	
}

void ABaseProjectile::SetMoveDirection(const FVector& Direction)
{
	MoveDirection = Direction;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComponent->Velocity = MoveDirection * ProjectileMovementComponent->InitialSpeed;

	SetLifeSpan(LifeSpan);
}
