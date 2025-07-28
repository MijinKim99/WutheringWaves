// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWEnemyGroup.generated.h"


class IWWHUDSharedUIInterface;
class UWWHUDSharedUIComponent;
class UEnemyUIComponent;
class UWWUserWidget;
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
	// 음수로 지정 시 표시 안함, EnemySpawnInfoArray의 인덱스 지정 시 해당 적 HP를 HUD에 표시
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	// int32 OwnerIndexOfEnemyHPBarOnHUD = -1;
	// UWWHUDSharedUIComponent* CachedHUDSharedUIComponent;
	//
	// UFUNCTION()
	// void DelegateTestFunction(float TestFloat);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// void InitializeHUDHPBar();
	UFUNCTION(BlueprintCallable)
	void EnemyDead(AActor* DeadEnemy);

protected:
	void SpawnEnemies();

public:
	FOnAllEnemyDeadDelegate OnAllEnemyDead;
};
