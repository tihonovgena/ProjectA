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
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY(PlayerCharacter);

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	check(HealthComponent);
	
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

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
		UE_LOG(LogTemp, Display, TEXT("%f"), CameraDirection->GetForwardVector().GetSafeNormal() );
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

