// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

struct FGameplayEffectSpecHandle;
class AEnemyAttackCollision;
class ATriggerBase;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	void SetAttackTransform(const FTransform& InTransform);
	UFUNCTION(BlueprintCallable, Category = "Enemy Combat Component")
	void SpawnAttackCollision(const TSubclassOf<AEnemyAttackCollision>& AttackCollision, const FGameplayEffectSpecHandle& GameplayEffectSpecHandle);
	
protected:
	FTransform AttackTransform;
	
};
