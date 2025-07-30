// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Common/WWDebugHelper.h"
#include "YHG/DataAssets/Input/InputConfig.h"
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
	void BindNativeInputAction(
		const UInputConfig* InInputConfig,
		const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, 
	UserObject* ContextObject,
	CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(
		const UInputConfig* InInputConfig,
		UserObject* ContextObject,
		CallbackFunc InputPressedFunc,
		CallbackFunc InputRelesedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UWWEnhancedInputComponent::BindNativeInputAction(const UInputConfig* InInputConfig, const FGameplayTag& InInputTag, 
ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	if (!InInputConfig)
	{
		//Debug::Print(TEXT("WWEnhancedInputComponent : Can't find InInputConfig"));
		return;
	}
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
};

template<class UserObject, typename CallbackFunc>
inline void UWWEnhancedInputComponent::BindAbilityInputAction(const UInputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputRelesedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	for (const FWWInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelesedFunc, AbilityInputActionConfig.InputTag);
	}
}
