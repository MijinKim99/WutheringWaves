// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Components/WWHUDSharedUIComponent.h"

// Sets default values for this component's properties
UWWHUDSharedUIComponent::UWWHUDSharedUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UWWHUDSharedUIComponent::BroadcastHUDTimerEnabled(bool bEnabled)
{
	OnHUDTimerEnabled.Broadcast(bEnabled);
}

void UWWHUDSharedUIComponent::BroadcastHUDTimerUpdate(float TimerValue)
{
	OnHUDTimerUpdate.Broadcast(TimerValue);
}

