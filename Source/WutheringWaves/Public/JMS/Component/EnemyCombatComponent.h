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
	UFUNCTION(BlueprintPure, Category = "Enemy Combat Component")
	FTransform GetAttackTransform();

protected:
	virtual void BeginPlay() override;

protected:
	FTransform AttackTransform = FTransform::Identity;
};
