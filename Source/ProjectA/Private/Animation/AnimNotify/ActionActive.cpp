// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "Animation/AnimNotify/ActionActive.h"
#include "Interface/ActionMontageInterface.h"

void UActionActive::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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
