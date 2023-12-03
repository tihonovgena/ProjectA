// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API ULookAtTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULookAtTargetComponent();

	void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LookAtTarget")
	FRotator GetRotatorBetweenTarget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;

	UPROPERTY()
	TObjectPtr<AActor> Target;

	UPROPERTY(EditDefaultsOnly, Category="Update", meta = (ClampMin = "0.0"))
	float UpdateFrequency = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category="Rotation", meta = (ClampMin = "0.0"))
	float YawAngleToRotate = 60.f;

	UPROPERTY(EditDefaultsOnly, Category="Rotation", meta = (ClampMin = "0.0"))
	float InterpRotationSpeed = 8.0f;

	void LookAtTarget();
	FTimerHandle UpdaterTimer;

private:
	FRotator CalculateRotatorToTarget();
	void MakeRotate(FRotator Rotator);

	FRotator RotatorToTarget;
		
};
