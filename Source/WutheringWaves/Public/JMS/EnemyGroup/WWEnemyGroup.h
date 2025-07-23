// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWEnemyGroup.generated.h"

class UBoxComponent;
class UTextRenderComponent;
class AEnemyCharacter;

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyInfo")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyInfo", meta = (MakeEditWidget = true))
	FTransform SpawnTransform;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEnemyDeadDelegate);

UCLASS()
class WUTHERINGWAVES_API AWWEnemyGroup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWWEnemyGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 EnemyCount;
	bool bIsEnemyAllDead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Data")
	TArray<FEnemySpawnInfo> EnemySpawnInfoArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> SpawnedEnemies;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SendHUDHPBar();
	UFUNCTION(BlueprintCallable)
	void EnemyDead(AActor* DeadEnemy);

protected:
	void SpawnEnemies();

public:
	FOnAllEnemyDeadDelegate OnAllEnemyDead;
};
