// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ActionMontageInterface.h"
#include "Interface/HealthComponentInterface.h"
#include "PACharacter.generated.h"

class UCharacterConfig;
class UActionMontageComponent;
class UHealthComponent;

UCLASS()
class PROJECTA_API APACharacter : public ACharacter, public IActionMontageInterface, public IHealthComponentInterface
{
	GENERATED_BODY()

public:
	APACharacter();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
#pragma region Movement
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Movement")
	bool IsMoving();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Movement")
	float GetCharacterSpeed();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Movement")
	float GetMovementDegreesDirection();
#pragma endregion

#pragma region Health
protected:
	virtual void OnDeath();
	virtual void OnHealthChanged(float Health);
	virtual float GetHealthPercent() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

#pragma endregion

#pragma region ActionMontage
public:
	UActionMontageComponent* GetActionMontageComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterConfig* GetCharacterConfig();
	
	virtual void PlayActionMontage(UAnimMontage* AnimMontage) override;
	virtual void OnStartedActionMontage() override;
	virtual void OnActiveActionMontage() override;
	virtual void OnFinishedActionMontage() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UCharacterConfig* CharacterConfig = nullptr;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActionMontageComponent> ActionMontageComponent;
	
#pragma endregion
	
};
