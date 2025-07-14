// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AbilitySystem/WWAttributeSet.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyAttributeSet : public UWWAttributeSet
{
	GENERATED_BODY()
public:
	UEnemyAttributeSet();
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, PhysicalResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, IceResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, FireResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, LightningResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData WindResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, WindResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData LightResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, LightResistance)
	UPROPERTY(BlueprintReadOnly, Category="Resistance")
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DarkResistance)
private:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
};