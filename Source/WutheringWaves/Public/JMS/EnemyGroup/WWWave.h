// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWWave.generated.h"


class AWWEnemyGroup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveClearedDelegate);
UCLASS()
class WUTHERINGWAVES_API AWWWave : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWWWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void WaveStart();
	AWWEnemyGroup* const GetCurrentEnemyGroup() { return CurrentEnemyGroup; }
	FOnWaveClearedDelegate OnWaveCleared;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TSubclassOf<AWWEnemyGroup> WaveEnemyGroup;

	UPROPERTY(VisibleAnywhere)
	AWWEnemyGroup* CurrentEnemyGroup;

	UFUNCTION()
	void BroadcastWaveCleared();
};
