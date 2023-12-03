// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDetectorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangedNearesEnemySignature, APawn* NewEnemy)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UEnemyDetectorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyDetectorComponent();

	FOnChangedNearesEnemySignature OnChangedNearestEnemy;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EnemyDetector")
	APawn* GetNearestEnemy();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EnemyDetector")
	APawn* GetComponentOwnerPawn();

	UFUNCTION(BlueprintCallable, Category = "EnemyDetector")
	void SetDetectionRadius(float Radius);
	
protected:
	virtual void BeginPlay() override;
	
	TArray<APawn*> GetEnemies();
	void StartDetectorEnemyTimer();

private:
	void UpdateNearestEnemy();
	APawn* FindNearestEnemy();
	void SetNewEnemy(APawn* NewEnemy);
	bool CanBeDetected(APawn* Enemy);
	bool IsNearerThanThreshold(float& Threshold, const APawn* Enemy);
	bool DistanceInDetectionRange(const float Distance) const;
	
	UPROPERTY()
	TObjectPtr<AActor> ComponentOwner;

	UPROPERTY()
	TObjectPtr<APawn> CurrentEnemy;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyDetector", meta = (ClampMin = "0.0", AllowPrivateAccess = "true"))
	float UpdateFrequency = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "EnemyDetector", meta = (ClampMin = "0.0", AllowPrivateAccess = "true"))
	float DetectionRadius = 700.f;

	FTimerHandle UpdaterTimer;
		
};
