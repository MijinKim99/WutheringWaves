// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PlayerDamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerDamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	UPlayerDamageTaken();

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
