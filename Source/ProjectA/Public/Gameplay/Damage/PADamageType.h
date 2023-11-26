// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "PADamageType.generated.h"

UENUM()
enum class EDamageType : uint8
{
	Physical = 0 UMETA(DisplayName = "Physical"),
	Fire = 1 UMETA(DisplayName = "Fire"),
	Poison = 2 UMETA(DisplayName = "Poison")
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class PROJECTA_API UPADamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	EDamageType GetDamageType() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="DamageType", meta = (AllowPrivateAccess="true"))
	EDamageType DamageType = EDamageType::Physical;
};
