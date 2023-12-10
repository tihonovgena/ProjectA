// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionMontageInterface.generated.h"

UINTERFACE()
class UActionMontageInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECTA_API IActionMontageInterface
{
	GENERATED_BODY()

public:
	virtual void PlayActionMontage(UAnimMontage* AnimMontage);
	virtual void OnStartedActionMontage();
	virtual void OnActiveActionMontage();
	virtual void OnFinishedActionMontage();
};
