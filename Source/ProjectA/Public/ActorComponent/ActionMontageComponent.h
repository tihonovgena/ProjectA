// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionMontageComponent.generated.h"

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

	template <class T>
	void BeginAction(UAnimMontage* AnimMontage, T* FunctionsOwner, void(T::* OnActionStartedFunction)(), void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)(), bool bInterruptCurrentAction= false);

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
	
	if (FunctionsOwner)
	{
		OnActionActive.BindUObject(FunctionsOwner, OnActionActiveFunction);
	}
	
	StartAction(AnimMontage);
}

template <class T>
void UActionMontageComponent::BeginAction(UAnimMontage* AnimMontage, T* FunctionsOwner, void(T::* OnActionStartedFunction)(), void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)(), bool bInterruptCurrentAction)
{
	if (!CanStartNewAction(bInterruptCurrentAction)) return;
	
	if (FunctionsOwner)
	{
		OnActionStarted.BindUObject(FunctionsOwner, OnActionStartedFunction);
		OnActionActive.BindUObject(FunctionsOwner, OnActionActiveFunction);
		OnActionFinished.BindUObject(FunctionsOwner, OnActionFinishedFunction);
	}
	
	StartAction(AnimMontage);
}
