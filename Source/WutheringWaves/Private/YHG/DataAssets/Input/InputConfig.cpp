// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaves/Public/YHG/DataAssets/Input/InputConfig.h"

UInputAction* UInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FWWInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}