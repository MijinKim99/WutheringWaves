// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWObjectPool.generated.h"

class AWWPooledObject;

UCLASS()
class WUTHERINGWAVES_API AWWObjectPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWObjectPool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	AWWPooledObject* SpawnPooledObject(APawn* InInstigator);
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	TSubclassOf<AWWPooledObject> PooledObjectClass;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	int PoolSize = 20;
	
	UPROPERTY(EditAnywhere, Category = "Object Pool")
	float PooledObjectLifeTime = 20.0f;

	UFUNCTION()
	void OnPooledObjectDespawn(AWWPooledObject* PoolActor);

	void DeactivateAllPooledObjects();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AWWPooledObject*> ObjectPool;
	TArray<int> SpawnedPoolIndexes;
};
