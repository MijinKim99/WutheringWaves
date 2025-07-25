// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/EnemyGroup/WWEnemyGroup.h"

#include "Common/WWDebugHelper.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "JMS/Character/EnemyCharacter.h"

// Sets default values
AWWEnemyGroup::AWWEnemyGroup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void AWWEnemyGroup::BeginPlay()
{
	Super::BeginPlay();
	EnemyCount = EnemySpawnInfoArray.Num();
	if (EnemyCount > 0)
	{
		bIsEnemyAllDead = false;
		SpawnEnemies();
	}
	else
	{
		bIsEnemyAllDead = true;
	}
	
}

// Called every frame
void AWWEnemyGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWWEnemyGroup::EnemyDead(AActor* DeadEnemy)
{
	SpawnedEnemies.Remove(DeadEnemy);
	if (SpawnedEnemies.Num() == 0)
	{
		OnAllEnemyDead.Broadcast();
		Debug::Print(FString::Printf(TEXT("All Enemy Dead : %s"), *GetName()));
	}
}

void AWWEnemyGroup::SpawnEnemies()
{
	for (const FEnemySpawnInfo& EnemySpawnInfo : EnemySpawnInfoArray)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		// Owner를 등록 후 적 사망시 Owner에 접근해 사망 알림
		AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(EnemySpawnInfo.EnemyClass,
		                                                      GetActorLocation()+EnemySpawnInfo.SpawnTransform.GetLocation(),
		                                                      GetActorRotation()+EnemySpawnInfo.SpawnTransform.GetRotation().Rotator(),
		                                                      SpawnParameters);
		SpawnedEnemy->SetOwner(this);
		SpawnedEnemies.Add(SpawnedEnemy);
	}
}
