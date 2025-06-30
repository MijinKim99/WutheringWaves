// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/WWPawnExtensionComponent.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPawnUIComponent : public UWWPawnExtensionComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentHpChanged;
};
