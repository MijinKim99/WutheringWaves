// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaves/Public/YHG/DataAssets/Input/DataAsset_InputConfig.h"

#include "InputAction.h"
#include "Common/WWDebugHelper.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	UInputAction* const* FindResultAction = NativeInputActions.Find(InInputTag);
	if (!FindResultAction)
	{
		Debug::Print(TEXT("DataAsset_InputConfig : Can't find InputAction by tag"));
		return nullptr;
	}
	
	return *FindResultAction;
}