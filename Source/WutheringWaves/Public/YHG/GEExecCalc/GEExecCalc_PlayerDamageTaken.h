// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_PlayerDamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UGEExecCalc_PlayerDamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	UGEExecCalc_PlayerDamageTaken();

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
