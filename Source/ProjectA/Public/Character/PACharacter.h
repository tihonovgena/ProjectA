// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacter.generated.h"

UCLASS()
class PROJECTA_API APACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
