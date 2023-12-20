// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "Interface/LookAtTargetInterface.h"
#include "Interface/WeaponComponentInterface.h"
#include "PlayerCharacter.generated.h"

class ULookAtTargetComponent;
class UEnemyDetectorComponent;
class USpringArmComponent;
class UBaseInputConfigAsset;
class UCameraComponent;
class UInputMappingContext;
class UWeaponComponent;

DECLARE_LOG_CATEGORY_EXTERN(PlayerCharacter, Display, All);

struct FInputActionValue;

UENUM()
enum EMovementOrientationMode
{
	ToController = 0,
	ToMovementDirection = 1
};

UCLASS()
class PROJECTA_API APlayerCharacter : public APACharacter, public ILookAtTargetInterface, public IWeaponComponentInterface

{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

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
protected:
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health) override;
	
#pragma endregion

#pragma region Weapon
public:
	virtual USceneComponent* GetWeaponComponentOwnerMesh() override;
	virtual bool CanContinueAttack() override;
	virtual bool GetWeaponAmmo(FWeaponAmmo& WeaponAmmo) override;
	virtual bool GetWeaponDefaultAmmo(FWeaponAmmo& WeaponAmmo) override;
	UWeaponComponent* GetWeaponComponent();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;

	UFUNCTION()
	void OnWeaponNeedReload();
	
	void SwitchWeapon();

#pragma endregion

#pragma region Action
	virtual void OnStartedActionMontage() override;
	virtual void OnFinishedActionMontage() override;
	
#pragma endregion 
	
};
