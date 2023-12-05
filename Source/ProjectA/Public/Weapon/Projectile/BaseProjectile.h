// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class USphereComponent;

UCLASS(Abstract)
class PROJECTA_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	ABaseProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent; 
	
};
