// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Weapon/Projectile/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(20.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);

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
	check(SphereComponent);
	check(ProjectileMovementComponent);

	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
	ProjectileMovementComponent->Velocity = MoveDirection * ProjectileMovementComponent->InitialSpeed;
	SetLifeSpan(LifeSpan);
	SphereComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnProjectileHit);
}

void ABaseProjectile::MakeDamage()
{
	if(!GetWorld()) return;
	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		GetActorLocation(),
		DamageRadius,
		DamageTypeClass,
		{GetOwner()},
		this,
		GetOwnerController(),
		bDoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 12.f, FColor::Red, false, 5.f, 0, 1.f);
}

void ABaseProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	MakeDamage();
	Destroy();
}

AController* ABaseProjectile::GetOwnerController()
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
