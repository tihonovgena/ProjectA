// ProjectA, Tikhonov Gennadii, All Rights Reserved


#include "ActorComponent/ActionMontageComponent.h"
#include "Interface/ActionMontageInterface.h"

DEFINE_LOG_CATEGORY(ActionMontageComponent);

UActionMontageComponent::UActionMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UActionMontageComponent::OnStartedActionMontage()
{
	GetOwnerActionMontageInterface()->OnStartedActionMontage();
	if (OnActionStarted.IsBound())
	{
		OnActionStarted.Execute();
		UE_LOG(ActionMontageComponent, Display, TEXT("Owner:%s action started"), *GetOwner()->GetName());
	}
}

void UActionMontageComponent::OnActiveActionMontage()
{
	if (OnActionActive.IsBound())
	{
		OnActionActive.Execute();
		UE_LOG(ActionMontageComponent, Display, TEXT("Owner:%s action actived"), *GetOwner()->GetName());
	}
}

void UActionMontageComponent::OnFinishedActionMontage()
{
	GetWorld()->GetTimerManager().ClearTimer(AnimMontageTimerHandle);
	GetOwnerActionMontageInterface()->OnFinishedActionMontage();
	
	if (OnActionFinished.IsBound())
	{
		OnActionFinished.Execute();
		UE_LOG(ActionMontageComponent, Display, TEXT("Owner:%s action finished"), *GetOwner()->GetName());
	}
}


void UActionMontageComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UActionMontageComponent::StartAction(UAnimMontage* AnimMontage)
{
	if (!GetWorld() && !AnimMontage) return;
	
	OnStartedActionMontage();
	
	GetWorld()->GetTimerManager().SetTimer(AnimMontageTimerHandle, this, &UActionMontageComponent::FinishAction, AnimMontage->GetPlayLength(), false, -1);
	
	PlayAnimMontage(AnimMontage);

	HasCurrentAction = true;
}

void UActionMontageComponent::FinishAction()
{
	OnFinishedActionMontage();
	HasCurrentAction = false;
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

bool UActionMontageComponent::CanStartNewAction(bool bInterruptCurrentAction)
{
	if (HasCurrentAction)
	{
		if (bInterruptCurrentAction)
		{
			return true;
		}
		return false;
	}

	return  true;
	
}

void UActionMontageComponent::InterruptCurrentAction()
{
	
}

IActionMontageInterface* UActionMontageComponent::GetOwnerActionMontageInterface()
{
	if (GetOwner() && Cast<IActionMontageInterface>(GetOwner()))
	{
		return Cast<IActionMontageInterface>(GetOwner());
	}
	return nullptr;
}



