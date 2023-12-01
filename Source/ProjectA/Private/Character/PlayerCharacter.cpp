// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Input/BaseInputConfigAsset.h"
#include "InputMappingContext.h"
#include "ActorComponent/HealthComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ActorComponent/WeaponComponent.h"

DEFINE_LOG_CATEGORY(PlayerCharacter);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	if (CameraSpringArm)
	{
		CameraSpringArm->SetupAttachment(GetRootComponent());
		CameraSpringArm->bInheritYaw = false;
	}
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	if (PlayerCamera)
	{
		PlayerCamera->SetupAttachment(CameraSpringArm);
	}
	
	CameraDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraDirection"));
	if (CameraDirection)
	{
		CameraDirection->SetupAttachment(CameraSpringArm);
	}
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(WeaponComponent);
	
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &APlayerCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &APlayerCharacter::OnHealthChanged);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	SetupMappingContext();
	BindInputActions(PlayerInputComponent);
}

void APlayerCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
}

void APlayerCharacter::OnHealthChanged(float Health)
{
	UE_LOG(PlayerCharacter, Display, TEXT("Player %s has new health - %f"), *GetName(), Health);
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
}

