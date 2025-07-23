// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ExecuteWave.generated.h"

class AWWWave;
class AWWEnemyGroup;
/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveClearDelegate);

UCLASS()
class WUTHERINGWAVES_API UExecuteWave : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WWWave")
	static UExecuteWave* ExecuteWave(AWWWave* WaveReferenceOnLevel);

protected:
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnWaveClearDelegate OnWaveClear;

	UFUNCTION()
	void BroadCastOnWaveClear();

protected:
	AWWWave* CurrentWave;
};
