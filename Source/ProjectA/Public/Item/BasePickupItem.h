// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickupItem.generated.h"

class USphereComponent;

UCLASS(Abstract)
class PROJECTA_API ABasePickupItem : public AActor
{
	GENERATED_BODY()

public:
	ABasePickupItem();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual bool PickUpItem(APawn* Pawn);

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Respawn")
	float RespawnTime = 5.f;
	
	void ItemWasTaken();
	void RespawnItem();
	
};
