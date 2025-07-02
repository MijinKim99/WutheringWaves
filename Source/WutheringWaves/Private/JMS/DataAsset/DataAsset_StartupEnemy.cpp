// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/DataAsset/DataAsset_StartupEnemy.h"
#include "JMS/AbilitySystem/EnemyGameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"

void UDataAsset_StartupEnemy::GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(ASC, Level);
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = ASC->GetAvatarActor();
			AbilitySpec.Level = Level;
			ASC->GiveAbility(AbilitySpec);
		}
	}
}
