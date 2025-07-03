// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AbilitySystem/Abilities/WWGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyGameplayAbility : public UWWGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Ability")
	AEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Abililty")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Abililty")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat, FGameplayTag DamageTypeTag);

private:
	TWeakObjectPtr<AEnemyCharacter> CachedEnemyCharacter;
};
