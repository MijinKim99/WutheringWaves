// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerGameplayAbility.h"

#include "WWGameplayTags.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Controllers/WWPlayerController.h"


APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AWWPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AWWPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

FGameplayEffectSpecHandle UPlayerGameplayAbility::MakePlayerDamageGameplayEffectSpecHandle(
TSubclassOf<UGameplayEffect> Effect
	,float SkillDamage, FGameplayTag SkillTag, float Magnitude)
{
	check(Effect);

	//ContextHandle을 만들어서 타겟정보 주입
	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	//SpecHandle을 만들어서 ContextHandle정보주입
	FGameplayEffectSpecHandle SpecHandle = GetWWAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

	//연산에 필요한 정보 주입
	SpecHandle.Data->SetSetByCallerMagnitude(
		WWGameplayTags::Shared_SetByCaller_SkillDamage,
		SkillDamage
		);

	if (SkillTag.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(SkillTag, Magnitude);
	}

	return SpecHandle;
}
