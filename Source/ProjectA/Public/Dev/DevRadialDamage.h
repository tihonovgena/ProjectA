// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevRadialDamage.generated.h"

class UPADamageType;
class USphereComponent;

UCLASS()
class PROJECTA_API ADevRadialDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevRadialDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickDamage = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoFullDamage = false;

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> Scene;
};
