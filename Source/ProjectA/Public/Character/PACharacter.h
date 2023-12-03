// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacter.generated.h"

class UHealthComponent;

UCLASS()
class PROJECTA_API APACharacter : public ACharacter
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

#pragma endregion	
};
