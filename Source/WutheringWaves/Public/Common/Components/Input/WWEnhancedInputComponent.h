// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Common/WWDebugHelper.h"
#include "YHG/DataAssets/Input/DataAsset_InputConfig.h"
#include "WWEnhancedInputComponent.generated.h"
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, 
	UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UWWEnhancedInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	if (!InInputConfig)
	{
		Debug::Print(TEXT("WWEnhancedInputComponent : Can't find InInputConfig"));
		return;
	}
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template <class UserObject, typename CallbackFunc>
inline void UWWEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
	UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	if (!InInputConfig)
	{
		Debug::Print(TEXT("WWEnhancedInputComponent : Can't find InInputConfig"));
		return;
	}
	for (const TPair<const UInputAction*, FGameplayTag>& Pair : InInputConfig->AbilityInputActions)
	{
		const UInputAction* InputAction = Pair.Key;
		const FGameplayTag& InputTag = Pair.Value;

		if (!InputAction || !InputTag.IsValid())
		{
			continue;
		}

		BindAction(InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, InputTag);
		BindAction(InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, InputTag);
	}
}
