// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecClac_EnemyDamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UGEExecClac_EnemyDamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	UGEExecClac_EnemyDamageTaken();

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
