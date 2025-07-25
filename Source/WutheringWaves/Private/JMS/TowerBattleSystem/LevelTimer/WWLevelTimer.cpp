// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/LevelTimer/WWLevelTimer.h"

// Sets default values
AWWLevelTimer::AWWLevelTimer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AWWLevelTimer::BroadcastOnTimerUpdateDelegate(float NewTime)
{
	OnTimerUpdate.Broadcast(NewTime);
}

void AWWLevelTimer::BroadcastOnTimerEndDelegate()
{
	OnTimerEnd.Broadcast();
}

void AWWLevelTimer::StartTimer(float Duration, float Interval)
{
	TimerDuration = Duration;
	CurrentTime = TimerDuration;
	TimerInterval = Interval;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWWLevelTimer::TickTimer, TimerInterval, true);
}

void AWWLevelTimer::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AWWLevelTimer::TickTimer()
{
	CurrentTime -= TimerInterval;
	BroadcastOnTimerUpdateDelegate(CurrentTime);
	if (CurrentTime <= 0.f)
	{
		BroadcastOnTimerEndDelegate();
		StopTimer();
	}
}
