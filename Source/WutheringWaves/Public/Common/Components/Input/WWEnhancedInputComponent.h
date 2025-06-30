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
};

template<class UserObject, typename CallbackFunc>
inline void UWWEnhancedInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	if (!InInputConfig)
	{
		Debug::Print(TEXT("WWEnhancedInputComponent : Can't find InInputConfig by tag"));
		return;
	}
	if (UInputAction* FoundAction = InInputConfig->FindInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}