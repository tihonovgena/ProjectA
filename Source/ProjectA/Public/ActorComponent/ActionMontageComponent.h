// ProjectA, Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionMontageComponent.generated.h"

DECLARE_DELEGATE(FOnActionStartedSignature);
DECLARE_DELEGATE(FOnActionActiveSignature);
DECLARE_DELEGATE(FOnActionFinishedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTA_API UActionMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionMontageComponent();
	
	template <class T>
	void BeginAction(UAnimMontage* AnimMontage, void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)());

	template <class T>
	void BeginAction(UAnimMontage* AnimMontage, void(T::* OnActionStartedFunction)(), void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)());

	void OnStartedActionMontage();
	void OnActiveActionMontage();
	void OnFinishedActionMontage();
	
	FOnActionStartedSignature OnActionStarted;
	FOnActionActiveSignature OnActionActive;
	FOnActionFinishedSignature OnActionFinished;

protected:
	virtual void BeginPlay() override;

	void PlayAnimMontage(UAnimMontage* AnimMontage);

};

template <class T>
void UActionMontageComponent::BeginAction(UAnimMontage* AnimMontage, void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)())
{
	T* CastedOwner = Cast<T>(GetOwner());
	if (CastedOwner)
	{
		OnActionActive.BindUObject(CastedOwner, OnActionActiveFunction);
		OnActionFinished.BindUObject(CastedOwner, OnActionFinishedFunction);
	}
	PlayAnimMontage(AnimMontage);
}

template <class T>
void UActionMontageComponent::BeginAction(UAnimMontage* AnimMontage, void(T::* OnActionStartedFunction)(), void(T::* OnActionActiveFunction)(), void(T::* OnActionFinishedFunction)())
{
	T* CastedOwner = Cast<T>(GetOwner());
	if (CastedOwner)
	{
		OnActionStarted.BindUObject(CastedOwner, OnActionStartedFunction);
		OnActionActive.BindUObject(CastedOwner, OnActionActiveFunction);
		OnActionFinished.BindUObject(CastedOwner, OnActionFinishedFunction);
	}
	PlayAnimMontage(AnimMontage);
}
