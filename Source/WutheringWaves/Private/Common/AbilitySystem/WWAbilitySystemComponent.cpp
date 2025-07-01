// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AbilitySystem/WWAbilitySystemComponent.h"

#include "Common/WWGameplayTags.h"

void UWWAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	//주입한 스펙으로 입력 실행
	for ( const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		//InputTag_Toggle의 태그가 있으면 Toggle On/OFF 처리
		if (InputTag.MatchesTag(WWGameplayTags::InputTag_Toggle))
		{
			if (Spec.IsActive())
			{
				CancelAbilityHandle(Spec.Handle);
			}
			else
			{
				TryActivateAbility(Spec.Handle);
			}
		}
		else
		{
			TryActivateAbility(Spec.Handle);
		}
	}
}

void UWWAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid() || !InputTag.MatchesTag(WWGameplayTags::InputTag_Hold))
	{
		return;
	}

	for ( FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		//런타임에서 어빌리티가 발동중인지
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag) && Spec.IsActive())
		{
			CancelAbilityHandle(Spec.Handle);
		}
	}
}

bool UWWAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag Tag)
{
	check(Tag.IsValid());

	TArray<FGameplayAbilitySpec*> AbilitySpecs;

	//이 함수는 활성화 가능한 모든 게임어빌리티 스팩을 가져온다.
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	//AbilitySpecs 배열에 받은 데이터가 유효하면
	if(!AbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() -1);
		FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

		check(AbilitySpec);

		if (!AbilitySpec->IsActive())
		{
			return TryActivateAbility(AbilitySpec->Handle);
		}
	}

	return false;
}
