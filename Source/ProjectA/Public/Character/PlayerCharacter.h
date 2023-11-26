// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "PlayerCharacter.generated.h"

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
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Camera")
	UArrowComponent* CameraDirection;
#pragma endregion 

#pragma region PlayerMovement
protected:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	
#pragma endregion
	
#pragma region Input
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupMappingContext() const;
	void BindInputActions(UInputComponent* PlayerInputComponent);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	TSoftObjectPtr<UBaseInputConfigAsset> InputActionAssets;
#pragma endregion 
	
	
};
