// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/WeaponComponent.h"

#include "SkeletalDebugRendering.h"
#include "Weapon/PAWeapon.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY(WeaponComponent)

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer
		(FireTimer, this, &UWeaponComponent::Fire, FireRate, true);
	}
	
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld() || !GetOwnerMesh() || !WeaponClass) return;
	
	const auto Weapon = GetWorld()->SpawnActor<APAWeapon>(WeaponClass);
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetOwnerMesh(), AttachmentRules, AttachSocketName);
	
}

USceneComponent* UWeaponComponent::GetOwnerMesh() const
{
	if (!GetOwner()) return nullptr;
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;
	return  Character->GetMesh();
}

void UWeaponComponent::Fire()
{
	UE_LOG(WeaponComponent, Display, TEXT("Fire!"));
}

