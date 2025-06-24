// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "WWEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WWCOPY_API UWWEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
		const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent,
		UserObject* ContextObject, CallbackFunc Func)
	{
		checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with Binding"));
		if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
		{
			BindAction(FoundAction, TriggerEvent, ContextObject, Func);
		}
	}

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
		UserObject* ContextObject,CallbackFunc InputPressedFunc,CallbackFunc InputReleasedFunc
		);
};

template <class UserObject, typename CallbackFunc>
void UWWEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with binding"));

	for ( const FBaseInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started,
			ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed,
			ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
}
