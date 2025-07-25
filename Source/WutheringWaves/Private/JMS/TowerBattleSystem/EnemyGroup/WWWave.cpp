// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/EnemyGroup/WWWave.h"

#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "JMS/TowerBattleSystem/EnemyGroup/WWEnemyGroup.h"

// Sets default values
AWWWave::AWWWave()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWWWave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWWWave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWWWave::WaveStart()
{
	CurrentEnemyGroup = GetWorld()->SpawnActor<AWWEnemyGroup>(WaveEnemyGroup, GetActorLocation(), GetActorRotation());
	CurrentEnemyGroup->OnAllEnemyDead.AddUniqueDynamic(this, &AWWWave::BroadcastWaveCleared);
}

void AWWWave::BroadcastWaveCleared()
{
	OnWaveCleared.Broadcast();
}
