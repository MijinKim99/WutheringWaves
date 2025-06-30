// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AbilitySystem/WWAbilitySystemComponent.h"

void UWWAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	//주입한 스펙으로 입력 실행
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		TryActivateAbility(Spec.Handle);
	}
}

void UWWAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}