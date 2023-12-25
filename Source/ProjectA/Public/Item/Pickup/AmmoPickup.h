// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Item/BasePickupItem.h"
#include "AmmoPickup.generated.h"

UCLASS()
class PROJECTA_API AAmmoPickup : public ABasePickupItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAmmoPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
