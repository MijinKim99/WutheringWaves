// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WWPooledObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, AWWPooledObject*, PoolActor);

UCLASS()
class WUTHERINGWAVES_API AWWPooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWWPooledObject();

	FOnPooledObjectDespawn OnPooledObjectDespawn;

	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
	virtual void Deactivate();

	virtual void SetActive(bool IsActive, APawn* InInstigator);
	void SetLifeTime(float InLifeTime);
	void SetPoolIndex(int InIndex);

	bool IsActive();
	int GetPoolIndex();
	
protected:
	bool bIsActive;
	float LifeTime;
	int PoolIndex;

	FTimerHandle LifeTimeTimerHandle;

};
