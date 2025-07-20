// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/ObjectPool/WWObjectPool.h"

#include "Common/ObjectPool/WWPooledObject.h"

// Sets default values
AWWObjectPool::AWWObjectPool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

AWWPooledObject* AWWObjectPool::SpawnPooledObject(APawn* InInstigator)
{
	for (AWWPooledObject* PoolableActor : ObjectPool)
	{
		if (PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true, InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}

	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.Remove(PooledObjectIndex);
		AWWPooledObject* PoolableActor = ObjectPool[PooledObjectIndex];
		if (PoolableActor != nullptr)
		{
			PoolableActor->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PoolableActor->SetLifeTime(PooledObjectLifeTime);
			PoolableActor->SetActive(true, InInstigator);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());
			return PoolableActor;
		}
	}

	return nullptr;
}

void AWWObjectPool::OnPooledObjectDespawn(AWWPooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

void AWWObjectPool::DeactivateAllPooledObjects()
{
	while (SpawnedPoolIndexes.Num() > 0)
	{
		ObjectPool[SpawnedPoolIndexes[0]]->Deactivate();
	}
}

// Called when the game starts or when spawned
void AWWObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				AWWPooledObject* PoolableActor = World->SpawnActor<AWWPooledObject>(
					PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator);
				if (PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false, nullptr);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &AWWObjectPool::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
}
