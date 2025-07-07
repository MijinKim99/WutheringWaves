// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

class AEnemyAttackCollision_Box;
struct FGameplayEffectSpecHandle;
class AEnemyAttackCollision;
class ATriggerBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyAttackCollisionInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxExtent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
};


UCLASS()
class WUTHERINGWAVES_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	void SetAttackTransform(const FTransform& InTransform);
	UFUNCTION(BlueprintCallable, Category = "Enemy Combat Component")
	void EnableAttackCollisionForAWhile(const FEnemyAttackCollisionInfo& AttackCollisionInfo,
	                                    const FGameplayEffectSpecHandle& GameplayEffectSpecHandle);
	UFUNCTION(BlueprintCallable, Category = "Enemy Combat Component")
	void LaunchCollisionProjectile(const FEnemyAttackCollisionInfo& AttackCollisionInfo,
	                                                   const FGameplayEffectSpecHandle& GameplayEffectSpecHandle);
	void OnHitTargetActor(AActor* HitActor);

protected:
	virtual void BeginPlay() override;

	FGameplayEffectSpecHandle GameplayEffectSpecHandleCache;
	TSet<AActor*> HitTargetSet;

	void SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);

protected:
	FTransform AttackTransform;
	FVector BoxExtentOnAttack;
};
