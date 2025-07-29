// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Character/EnemyCharacter.h"
#include "EliteEnemyCharacter.generated.h"

class UWWUserWidget;
class UEliteAttributeSet;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEliteEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEliteEnemyCharacter();
	
	// Parry
public:
	UFUNCTION(BlueprintCallable, Category = "Parry")
	void StartParryEvent();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float ParryGuideDuration = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float ParryEnableDuration = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parry")
	float UpdateInterval = 0.05f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parry")
	float ParryGuideDurationCounter = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parry")
	float ParryEnableDurationCounter = 0.0f;;
	UFUNCTION(BlueprintNativeEvent, Category = "Parry")
	void EnableParry();
	UFUNCTION(BlueprintNativeEvent, Category = "Parry")
	void DisableParry();
	UFUNCTION(BlueprintNativeEvent, Category = "Parry")
	void UpdateGuideDuration();
	UFUNCTION(BlueprintNativeEvent, Category = "Parry")
	void UpdateEnableDuration();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEliteAttributeSet* EliteAttributeSet;
	FTimerHandle EnableParryTimerHandle;
	FTimerHandle DisableParryTimerHandle;
	FTimerHandle UpdateGuideDurationTimerHandle;
	FTimerHandle UpdateEnableDurationTimerHandle;

// UI
public:
	UFUNCTION(BlueprintCallable, Category = "Enemy UI")
	TSubclassOf<UWWUserWidget> GetEnemyUIForHUD();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy UI")
	TSubclassOf<UWWUserWidget> EnemyUIForHUD;
	
};
