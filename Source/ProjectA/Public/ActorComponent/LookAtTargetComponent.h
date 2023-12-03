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

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;

	UPROPERTY()
	TObjectPtr<AActor> Target;

	UPROPERTY(EditDefaultsOnly, Category="Update", meta = (ClampMin = "0.0"))
	float UpdateFrequency = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category="Update", meta = (ClampMin = "0.0"))
	float StartRotateYawDegrees = 80.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Update", meta = (ClampMin = "0.0"))
	float StartRotatePithDegrees = 80.f;

	void LookAtTarget();
	FTimerHandle UpdaterTimer;

private:
	void CalculateAnglesToTarget(float& YawDegrees, float& PitchDegrees);
	void MakeRotate(FRotator Rotator);
		
};
