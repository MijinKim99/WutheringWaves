// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWLevelTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdateDelegate, float, NewTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerEndDelegate);


UCLASS()
class WUTHERINGWAVES_API AWWLevelTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWLevelTimer();
public:
	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdateDelegate OnTimerUpdate;
	UPROPERTY(BlueprintAssignable)
	FOnTimerEndDelegate OnTimerEnd;

protected:
	float TimerDuration;
	float CurrentTime;
	float TimerInterval;
	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "Level Timer")
	void BroadcastOnTimerUpdateDelegate(float NewTime);
	UFUNCTION(BlueprintCallable, Category = "Level Timer")
	void BroadcastOnTimerEndDelegate();
	UFUNCTION(BlueprintCallable, Category = "Level Timer")
	void StartTimer(float Duration,float Interval = 0.1f);
	UFUNCTION(BlueprintCallable, Category = "Level Timer")
	void StopTimer();
protected:
	void TickTimer();
};
