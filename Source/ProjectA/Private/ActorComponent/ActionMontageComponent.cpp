// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/ActionMontageComponent.h"
#include "Interface/ActionMontageInterface.h"


UActionMontageComponent::UActionMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UActionMontageComponent::OnStartedActionMontage()
{
	if (OnActionStarted.IsBound())
	{
		OnActionStarted.Execute();
	}
}

void UActionMontageComponent::OnActiveActionMontage()
{
	if (OnActionActive.IsBound())
	{
		OnActionActive.Execute();
	}
}

void UActionMontageComponent::OnFinishedActionMontage()
{
	if (OnActionFinished.IsBound())
	{
		OnActionFinished.Execute();
	}
}


void UActionMontageComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UActionMontageComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	if(!IsValid(GetOwner())) return;
	IActionMontageInterface* ActionMontageInterface = Cast<IActionMontageInterface>(GetOwner());
	if (ActionMontageInterface)
	{
		ActionMontageInterface->PlayActionMontage(AnimMontage);
	}
}



