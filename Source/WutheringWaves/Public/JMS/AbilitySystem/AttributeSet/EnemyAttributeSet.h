// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IWWHUDSharedUIInterface;
class IPawnUIInterface;

UCLASS()
class WUTHERINGWAVES_API UEnemyAttributeSet : public UAttributeSet
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
	// TWeakInterfacePtr<IWWHUDSharedUIInterface> CachedHUDSharedUIInterface;
protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};