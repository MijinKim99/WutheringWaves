// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AbilitySystem/WWAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerAttributeSet : public UWWAttributeSet
{
	GENERATED_BODY()

public:
	UPlayerAttributeSet();

	//현재 스테미나
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentStamina)
	//최대 스테미나
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxStamina)
	
	//적용 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyEnergyRegen;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ApplyEnergyRegen)
	//기본 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicEnergyRegen;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, BasicEnergyRegen)

	//적용 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalRate;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ApplyCriticalRate)
	//기본 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalRate;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, BasicCriticalRate)

	//적용 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ApplyCriticalDamage)
	//기본 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, BasicCriticalDamage)


	
	//속성별 피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyFireDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicFireDamage;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyIceDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicIceDamage;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAirDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAirDamage;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyElectricDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicElectricDamage;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyLightDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicLightDamage;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDarkDamage;
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDarkDamage;
};
