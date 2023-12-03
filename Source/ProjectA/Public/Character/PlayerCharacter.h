// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "Interface/LookAtEnemyInterface.h"
#include "PlayerCharacter.generated.h"

class ULookAtTargetComponent;
class UEnemyDetectorComponent;
DECLARE_LOG_CATEGORY_EXTERN(PlayerCharacter, Display, All);

struct FInputActionValue;
class UHealthComponent;
class USpringArmComponent;
class UBaseInputConfigAsset;
class UCameraComponent;
class UInputMappingContext;
class UWeaponComponent;

UENUM()
enum EMovementOrientationMode
{
	ToController = 0,
	ToMovementDirection = 1
};

UCLASS()
class PROJECTA_API APlayerCharacter : public APACharacter,
public IEnemyDetectorInterface, public ILookAtEnemyInterface

{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual bool CanBeDetected() override;

protected:
	virtual void BeginPlay() override;

#pragma region EnemyDetector
public:
	UFUNCTION(BlueprintCallable)
	APawn* GetNearestEnemy();

protected:
	void OnChangedNearestEnemy(APawn* NewEnemy);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyDetectorComponent> EnemyDetectorComponent;

#pragma endregion 	
	
#pragma region Camera
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> CameraDirection;
#pragma endregion 

#pragma region PlayerMovement
public:
	UFUNCTION()
	virtual void MakeRotateToTarget(FRotator Rotator) override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	void SetMovementOrientationMode(EMovementOrientationMode Mode);

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULookAtTargetComponent> LookAtTargetComponent;
	
#pragma endregion
	
#pragma region Input
private:
	void SetupMappingContext() const;
	void BindInputActions(UInputComponent* PlayerInputComponent);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UBaseInputConfigAsset> InputActionAssets;
	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
#pragma endregion 

#pragma region Health
private:
	virtual void OnDeath() override;
	void OnHealthChanged(float Health);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

#pragma endregion

#pragma region Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;
#pragma endregion

	
};
