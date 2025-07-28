// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KMJ/UIComponents/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetEnableDelegate, bool, bIsEnabled);
UCLASS()
class WUTHERINGWAVES_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentStaggerChanged;
	UPROPERTY(BlueprintAssignable)
	FOnSetEnableDelegate OnSetParryGuideEnable;
	UPROPERTY(BlueprintAssignable)
	FOnSetEnableDelegate OnSetParryEnable;
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnReadyForParryUpdate;
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnParryUpdate;
};
