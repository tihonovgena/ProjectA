// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "PlayerCharacter.generated.h"

class UHealthComponent;
struct FInputActionValue;
class USpringArmComponent;
DECLARE_LOG_CATEGORY_EXTERN(PlayerCharacter, Display, All);

class UBaseInputConfigAsset;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class PROJECTA_API APlayerCharacter : public APACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;
	
	void OnDeath();
	void OnHealthChanged(float Health);
#pragma endregion 
	
};
