// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Animation/AnimNotify/AnimNotify_ActionActive.h"
#include "Interface/ActionMontageInterface.h"

void UAnimNotify_ActionActive::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if(IsValid(MeshComp) && MeshComp->GetOwner())
	{
		IActionMontageInterface* ActionMontageInterface = Cast<IActionMontageInterface>(MeshComp->GetOwner());
		if (ActionMontageInterface)
		{
			ActionMontageInterface->OnActiveActionMontage();
		}
	}
}
