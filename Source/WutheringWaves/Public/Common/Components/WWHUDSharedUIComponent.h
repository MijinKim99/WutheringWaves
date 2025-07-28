// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Widget/WWUserWidget.h"
#include "Components/ActorComponent.h"
#include "WWHUDSharedUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDTimerEnabledDelegate, bool, bEnabled);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDTimerUpdateDelegate, float, TimerValue);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetEnabledEnemyHUDHPBar, bool, bEnable, AActor*, UIOwner);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetEnemyHUDHPBarName, FText, CurrentEnemyNameAsFText);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateEnemyHUDHPBarHPPercent, float, EnemyHPPercent);
//
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateEnemyHUDHPBarStaggerPercent, float, EnemyStaggerPercent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUTHERINGWAVES_API UWWHUDSharedUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWWHUDSharedUIComponent();

protected:

public:
	UPROPERTY(BlueprintAssignable)
	FOnHUDTimerEnabledDelegate OnHUDTimerEnabled;
	UFUNCTION(BlueprintCallable)
	void BroadcastHUDTimerEnabled(bool bEnabled);
	UPROPERTY(BlueprintAssignable)
	FOnHUDTimerUpdateDelegate OnHUDTimerUpdate;
	UFUNCTION(BlueprintCallable)
	void BroadcastHUDTimerUpdate(float TimerValue);
	// UPROPERTY(BlueprintAssignable)
	// FOnSetEnabledEnemyHUDHPBar OnSetEnabledEnemyHUDHPBar;
	// UFUNCTION(BlueprintCallable)
	// void BroadcastSetEnabledEnemyHUDHPBar(bool bEnable, AActor* UIOwner);
	// UPROPERTY(BlueprintAssignable)
	// FOnSetEnemyHUDHPBarName OnSetEnemyHUDHPBarName;
	// UFUNCTION(BlueprintCallable)
	// void BroadcastSetEnemyHUDHPBarName(FText CurrentEnemyNameAsFText);
	// UPROPERTY(BlueprintAssignable)
	// FOnUpdateEnemyHUDHPBarHPPercent OnUpdateEnemyHUDHPBarHPPercent;
	// UFUNCTION(BlueprintCallable)
	// void BroadcastUpdateEnemyHUDHPBarHPPercent(float EnemyHPPercent);
	// UPROPERTY(BlueprintAssignable)
	// FOnUpdateEnemyHUDHPBarStaggerPercent OnUpdateEnemyHUDHPBarStaggerPercent;
	// UFUNCTION(BlueprintCallable)
	// void BroadcastUpdateEnemyHUDHPBarStaggerPercent(float EnemyStaggerPercent);
};
