// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerCharacter, Display, All);

struct FInputActionValue;
class UHealthComponent;
class USpringArmComponent;
class UBaseInputConfigAsset;
class UCameraComponent;
class UInputMappingContext;
class UWeaponComponent;

UCLASS()
class PROJECTA_API APlayerCharacter : public APACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
#pragma region Camera
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> CameraDirection;
#pragma endregion 

#pragma region PlayerMovement
protected:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

#pragma endregion

#pragma region Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;
#pragma endregion 
	
};
