// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Input/BaseInputConfigAsset.h"
#include "InputMappingContext.h"
#include "ActorComponent/ActionMontageComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorComponent/WeaponComponent.h"
#include "ActorComponent/EnemyDetectorComponent.h"
#include "ActorComponent/LookAtTargetComponent.h"
#include "Character/CharacterConfig/CharacterConfig.h"

DEFINE_LOG_CATEGORY(PlayerCharacter);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationYaw = false;
	
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	EnemyDetectorComponent = CreateDefaultSubobject<UEnemyDetectorComponent>(TEXT("EnemyDetector"));
	LookAtTargetComponent = CreateDefaultSubobject<ULookAtTargetComponent>(TEXT("LookAtTarget"));
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetRootComponent());
	CameraSpringArm->bInheritYaw = false;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraSpringArm);
	
	CameraDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraDirection"));
	CameraDirection->SetupAttachment(CameraSpringArm);
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponComponent);
	check(EnemyDetectorComponent);
	check(LookAtTargetComponent);

	WeaponComponent->WeaponNeedReload.AddUObject(this, &APlayerCharacter::OnWeaponNeedReload);
	EnemyDetectorComponent->OnChangedNearestEnemy.AddUObject(this, &APlayerCharacter::OnChangedNearestEnemy);
	
}

APawn* APlayerCharacter::GetNearestEnemy()
{
	return EnemyDetectorComponent->GetNearestEnemy();
}

void APlayerCharacter::OnChangedNearestEnemy(APawn* NewEnemy)
{
	LookAtTargetComponent->SetTarget(NewEnemy);

	// Sets controller Yaw in depended of rotation mode, if there are no any enemies will use orient to movement direction
	if (IsValid(NewEnemy))
	{
		SetMovementOrientationMode(EMovementOrientationMode::ToController);
		WeaponComponent->StartAttack();
		UE_LOG(PlayerCharacter, Display, TEXT("Got new enemy %s"), *NewEnemy->GetName());
	}
	else
	{
		WeaponComponent->StopAttack();
		SetMovementOrientationMode(EMovementOrientationMode::ToMovementDirection);
		UE_LOG(PlayerCharacter, Display, TEXT("Does not have any enemy"));
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlayerCharacter::MakeRotateToTarget(FRotator Rotator)
{
	if (!GetController()) return;
	GetController()->SetControlRotation(Rotator);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	if (MoveValue.Y != 0.0f)
	{
		AddMovementInput(CameraDirection->GetForwardVector(), MoveValue.Y);
	}

	if (MoveValue.X != 0.0f)
	{
		AddMovementInput(CameraDirection->GetRightVector(), MoveValue.X);
	}
	
}

void APlayerCharacter::SetMovementOrientationMode(EMovementOrientationMode Mode)
{
	switch (Mode)
	{
	case EMovementOrientationMode::ToController:
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	
	case EMovementOrientationMode::ToMovementDirection:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	SetupMappingContext();
	BindInputActions(PlayerInputComponent);
}

void APlayerCharacter::OnDeath()
{
	Super::OnDeath();
	WeaponComponent->StopAttack();
	EnemyDetectorComponent->Deactivate();
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
}

void APlayerCharacter::OnHealthChanged(float Health)
{
	UE_LOG(PlayerCharacter, Display, TEXT("Player %s has new health - %f"), *GetName(), Health);
}

USceneComponent* APlayerCharacter::GetWeaponComponentOwnerMesh()
{
	return GetMesh();
}

bool APlayerCharacter::CanContinueAttack()
{
	return IsValid(GetNearestEnemy());
}

bool APlayerCharacter::GetWeaponAmmo(FWeaponAmmo& WeaponAmmo)
{
	return WeaponComponent->GetWeaponAmmo(WeaponAmmo);
}

bool APlayerCharacter::GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo)
{
	return WeaponComponent->GetWeaponDefaultAmmo(WeaponAmmo);
}

UWeaponComponent* APlayerCharacter::GetWeaponComponent()
{
	return WeaponComponent;
}

void APlayerCharacter::OnWeaponNeedReload()
{
	const EWeaponType EquipWeaponType = GetWeaponComponent()->GetEquipWeaponType();
	UAnimMontage* ReloadWeaponMontage = CharacterConfig->GetReloadWeaponAnimMontage(EquipWeaponType);
	
	GetActionMontageComponent()->BeginAction(
		ReloadWeaponMontage,
		WeaponComponent,
		&UWeaponComponent::ReloadWeapon,
		true);
}

void APlayerCharacter::SwitchWeapon()
{
	const EWeaponType EquipWeaponType = GetWeaponComponent()->GetEquipWeaponType();
	UAnimMontage* SwitchWeaponMontage = CharacterConfig->GetSwitchWeaponAnimMontage(EquipWeaponType);
	
	GetActionMontageComponent()->BeginAction(
		SwitchWeaponMontage,
		WeaponComponent,
		&UWeaponComponent::SwitchWeapon,
		true);
}

void APlayerCharacter::OnStartedActionMontage()
{
	WeaponComponent->StopAttack();
}

void APlayerCharacter::OnFinishedActionMontage()
{
	if (IsValid(GetNearestEnemy()))
	{
		WeaponComponent->StartAttack();
	}
}

void APlayerCharacter::SetupMappingContext() const
{
	const UInputMappingContext* InputMappingContext = InputMapping.LoadSynchronous();
	check(InputMappingContext)
	
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Setup mapping context is fail - PlayerController is null."));
		return;
	}
	
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Setup mapping context is fail - LocalPlayer is null."));
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* LocalInputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!LocalInputSubsystem)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Setup mapping context is fail - LocalInputSubsystem is null."));
		return;
	}
	
	LocalInputSubsystem->AddMappingContext(InputMappingContext, 0);
}

void APlayerCharacter::BindInputActions(UInputComponent* PlayerInputComponent)
{
	const UBaseInputConfigAsset* ActionAsset = InputActionAssets.LoadSynchronous();
	check(ActionAsset);
	
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!PlayerEnhancedInputComponent)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Bind input action fail - PlayerEnhancedInputComponent is null."));
		return;
	}
	
	PlayerEnhancedInputComponent->BindAction(ActionAsset->Movement, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	PlayerEnhancedInputComponent->BindAction(ActionAsset->SwitchWeapon, ETriggerEvent::Completed, this, &APlayerCharacter::SwitchWeapon);
}

