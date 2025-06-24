// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for ( FWWInputActionConfig NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.InputTag == InInputTag && NativeInputActionConfig.InputAction)
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	
	return nullptr;
}
