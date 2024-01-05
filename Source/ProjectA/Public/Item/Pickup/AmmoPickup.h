// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Item/BasePickupItem.h"
#include "AmmoPickup.generated.h"

enum class EAmmoType : uint8;

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
	virtual bool PickUpItem(APawn* Pawn) override;

	UPROPERTY(EditAnywhere, Category = "AmmpoPickup")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, Category = "AmmpoPickup", meta = (ClampMin = "1"))
	int32 Clips;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
