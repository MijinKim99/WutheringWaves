// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWEnemyGroup.generated.h"

class AEnemyCharacter;

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "EnemyInfo")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "EnemyInfo", meta = (MakeEditWidget = true))
	FTransform SpawnTransform;
	
};

UCLASS()
class WUTHERINGWAVES_API AWWEnemyGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWEnemyGroup();
#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
#endif
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	TArray<FEnemySpawnInfo> EnemySpawnInfoArray;

private:
	UPROPERTY()
	TArray<USkeletalMeshComponent*> SkeletalMeshVisualizers; 

};
