// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/Wave/ExecuteWave.h"

#include "JMS/TowerBattleSystem/EnemyGroup/WWEnemyGroup.h"
#include "JMS/TowerBattleSystem/EnemyGroup/WWWave.h"

UExecuteWave* UExecuteWave::ExecuteWave(UObject* WorldContextObject, TSubclassOf<AWWWave> Wave, FVector SpawnLocation,
                                        FRotator SpawnRotation)
{
	UExecuteWave* Node = NewObject<UExecuteWave>();
	Node->CurrentWave = WorldContextObject->GetWorld()->SpawnActor<AWWWave>(Wave, SpawnLocation, SpawnRotation);

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
