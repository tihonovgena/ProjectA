// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ActionActive.generated.h"


class UAnimNotify_PlaySound;

UCLASS()
class PROJECTA_API UActionActive : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
