// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WWHUDSharedUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDTimerEnabledDelegate, bool, bEnabled);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDTimerUpdateDelegate, float, TimerValue);

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
};
