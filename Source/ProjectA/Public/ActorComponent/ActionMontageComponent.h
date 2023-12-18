// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotify/AnimNotify_ActionActive.h"
#include "Components/ActorComponent.h"
#include "ActionMontageComponent.generated.h"

class UAnimNotify_ActionActive;
class IActionMontageInterface;
DECLARE_DELEGATE(FOnActionStartedSignature);
DECLARE_DELEGATE(FOnActionActiveSignature);
DECLARE_DELEGATE(FOnActionFinishedSignature);

DECLARE_LOG_CATEGORY_EXTERN(ActionMontageComponent, Display, All);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTA_API UActionMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionMontageComponent();
	
	template <class T>
	void BeginAction(UAnimMontage* AnimMontage, T* FunctionsOwner, void(T::* OnActionActiveFunction)(), bool bInterruptCurrentAction = false);

	void OnStartedActionMontage();
	void OnActiveActionMontage();
	void OnFinishedActionMontage();
	
	FOnActionStartedSignature OnActionStarted;
	FOnActionActiveSignature OnActionActive;
	FOnActionFinishedSignature OnActionFinished;

protected:
	virtual void BeginPlay() override;

private:
	void StartAction(UAnimMontage* AnimMontage);
	void FinishAction();
	void PlayAnimMontage(UAnimMontage* AnimMontage);
	bool CanStartNewAction(bool bInterruptCurrentAction);
	void InterruptCurrentAction();

	IActionMontageInterface* GetOwnerActionMontageInterface();
	
	bool HasCurrentAction;

	FTimerHandle AnimMontageTimerHandle;

};

template <class T>
void UActionMontageComponent::BeginAction(UAnimMontage* AnimMontage, T* FunctionsOwner, void(T::* OnActionActiveFunction)(), bool bInterruptCurrentAction)
{
	if (!CanStartNewAction(bInterruptCurrentAction)) return;

#if WITH_EDITOR
	
	checkf(AnimMontage, TEXT("No anim montage"))

	bool NotifyFound = false;
	const auto NotifyEvents = AnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto ActiveNotify = Cast<UAnimNotify_ActionActive>(NotifyEvent.Notify);
		if (ActiveNotify)
		{
			NotifyFound = true;
			break;
		}
	}

	checkf(NotifyFound, TEXT("Anim montage does not have action active notify"))
	
#endif
	
	if (FunctionsOwner)
	{
		OnActionActive.BindUObject(FunctionsOwner, OnActionActiveFunction);
	}
	
	StartAction(AnimMontage);
}
