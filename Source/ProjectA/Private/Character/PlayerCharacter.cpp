// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Character/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Input/BaseInputConfigAsset.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(PlayerCharacter);

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnableRotateToDirection = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
	CameraSpringArm->SetupAttachment(GetRootComponent());
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(CameraSpringArm);
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
		AddMovementInput(GetActorForwardVector(), MoveValue.Y);
	}

	if (MoveValue.X != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), MoveValue.X);
	}
	
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	SetupMappingContext();
	BindInputActions(PlayerInputComponent);
}

void APlayerCharacter::SetupMappingContext() const
{
	if (InputMapping.IsNull())
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Setup mapping context is fail - InputMapping is null."));
		return;
	}
	
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
	
	LocalInputSubsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
}

void APlayerCharacter::BindInputActions(UInputComponent* PlayerInputComponent)
{
	const UBaseInputConfigAsset* ActionAsset = InputActionAssets.LoadSynchronous();
	if (!ActionAsset)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Bind input action fail - InputActionAssets is null"));
		return;
	}
	
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!PlayerEnhancedInputComponent)
	{
		UE_LOG(PlayerCharacter, Warning, TEXT("Bind input action fail - PlayerEnhancedInputComponent is null."));
		return;
	}
	
	PlayerEnhancedInputComponent->BindAction(ActionAsset->Movement, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
}

