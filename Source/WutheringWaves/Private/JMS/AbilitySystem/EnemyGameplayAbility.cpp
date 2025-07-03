// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AbilitySystem/EnemyGameplayAbility.h"

#include "Common/WWGameplayTags.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "JMS/Character/EnemyCharacter.h"
#include "JMS/Component/EnemyCombatComponent.h"


AEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return Cast<UEnemyCombatComponent>(GetEnemyCharacterFromActorInfo()->GetPawnCombatComponent());
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	const FScalableFloat& DamageFloat, FGameplayTag DamageTypeTag)
{
	check(Effect);

	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetWWAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
	Effect,
	GetAbilityLevel(),
	ContextHandle
	);

	SpecHandle.Data->SetSetByCallerMagnitude(DamageTypeTag,
		DamageFloat.GetValueAtLevel(GetAbilityLevel()));
	
	return SpecHandle;
}