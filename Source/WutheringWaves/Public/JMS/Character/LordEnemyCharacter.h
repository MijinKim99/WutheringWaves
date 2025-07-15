// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Character/EliteEnemyCharacter.h"
#include "LordEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API ALordEnemyCharacter : public AEliteEnemyCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Parry")
	void StartParryEvent();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float ParryGuideDuration = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float ParryEnableDuration = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float UpdateInterval = 0.1f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parry")
	float ParryGuideDurationCounter = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parry")
	float ParryEnableDurationCounter = 0.0f;;

protected:
	void EnableParry();
	void DisableParry();
	void UpdateGuideDuration();
	void UpdateEnableDuration();
	FTimerHandle EnableParryTimerHandle;
	FTimerHandle DisableParryTimerHandle;
	FTimerHandle UpdateGuideDurationTimerHandle;
	FTimerHandle UpdateEnableDurationTimerHandle;
};
