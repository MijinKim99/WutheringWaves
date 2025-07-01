// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/AbilitySystem/Abilities/WWGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Common/Components/Combat/PawnCombatComponent.h"

UPawnCombatComponent* UWWGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWWAbilitySystemComponent* UWWGameplayAbility::GetWWAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWWAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UWWGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(ASC && SpecHandle.IsValid());

	return GetWWAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, ASC);
}

FActiveGameplayEffectHandle UWWGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle, EWWSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, SpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EWWSuccessType::Success : EWWSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

void UWWGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWWAbilityActivationPolicy::OnGiven)
	{
		//액터의 정보를 받아올 수 있거나 해당 어빌리티가 활성화 되지 않았으면
		if (ActorInfo && !Spec.IsActive())
		{
			//현재 가지고 있는 어빌리티를 발동시킨다.
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWWGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWWAbilityActivationPolicy::OnGiven)
	{
		//어빌리티가 유효한지 체크
		if (ActorInfo)
		{
			//클리어
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}