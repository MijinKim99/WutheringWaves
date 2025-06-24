// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WWAbilitySystemComponent.h"
#include "GameplayTagContainer.h"

void UWWAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	//주입한 스펙으로 입력 실행
	// If you want to lock the ability list during this operation, use the ABILITYLIST_SCOPE_LOCK() macro
	// ABILITYLIST_SCOPE_LOCK()
	for ( const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		TryActivateAbility(Spec.Handle);
	}
}

void UWWAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}
