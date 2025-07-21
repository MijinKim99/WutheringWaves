// Fill out your copyright notice in the Description page of Project Settings.

#include "YHG/AbilitySystem/Abilities/PlayerGameplayAbility.h"

#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Common/PlayerControllers/WWPlayerController.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	// if (!CachedPlayerCharacter.IsValid())
	// {
	// 	CachedPlayerCharacter = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
	// }
	//
	// return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
	return Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
}

AWWPlayerController* UPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AWWPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

//TODO :: 패링데미지 추가
FGameplayEffectSpecHandle UPlayerGameplayAbility::MakePlayerDamageGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect
		,float PlayerDamage, FGameplayTag AttackTypeTag, int32 ComboCount)
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
	/*SpecHandle.Data->SetSetByCallerMagnitude(
		WWGameplayTags::Shared_SetByCaller_Damage_Physical,
		PlayerDamage
		);*/

	if (AttackTypeTag.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(AttackTypeTag, PlayerDamage);
	}

	return SpecHandle;
}