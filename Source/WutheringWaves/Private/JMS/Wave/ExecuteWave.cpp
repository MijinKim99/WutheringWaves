// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Wave/ExecuteWave.h"

#include "JMS/EnemyGroup/WWEnemyGroup.h"
#include "JMS/EnemyGroup/WWWave.h"

UExecuteWave* UExecuteWave::ExecuteWave(AWWWave* WaveReferenceOnLevel)
{
	UExecuteWave* Node = NewObject<UExecuteWave>();
	Node->CurrentWave = WaveReferenceOnLevel;
	return Node;
}

void UExecuteWave::Activate()
{
	Super::Activate();
	CurrentWave->WaveStart();
	CurrentWave->OnWaveCleared.AddUniqueDynamic(this, &UExecuteWave::BroadCastOnWaveClear);
}

void UExecuteWave::BroadCastOnWaveClear()
{
	OnWaveClear.Broadcast();
}
