// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacter.h"
#include "Interface/EnemyDetectorInterface.h"
#include "AICharacter.generated.h"

UCLASS()
class PROJECTA_API AAICharacter : public APACharacter, public IEnemyDetectorInterface
{
	GENERATED_BODY()

public:
	AAICharacter();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual bool CanBeDetected() override;
	
protected:
	virtual void BeginPlay() override;

#pragma region Health
protected:
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health) override;
	
#pragma endregion
	
	
};
