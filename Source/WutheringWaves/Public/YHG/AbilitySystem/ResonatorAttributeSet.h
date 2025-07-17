// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "ResonatorAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IPawnUIInterface;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UResonatorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UResonatorAttributeSet();

	//현재 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, CurrentHp)
	//최대 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, MaxHp)

	//적용 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAttack;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyAttack)
	//기본 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAttack;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicAttack)

	//적용 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDefense;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyDefense)
	//기본 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDefense;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicDefense)
	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, DamageTaken)
	
	//적용 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyEnergyRegen;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyEnergyRegen)
	//기본 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicEnergyRegen;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicEnergyRegen)

	//적용 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalRate;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyCriticalRate)
	//기본 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalRate;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicCriticalRate)

	//적용 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyCriticalDamage)
	//기본 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicCriticalDamage)
	
	//속성별 피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyFireDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyFireDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicFireDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicFireDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyIceDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyIceDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicIceDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicIceDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAirDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyAirDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAirDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicAirDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyElectricDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyElectricDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicElectricDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicElectricDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyLightDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyLightDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicLightDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicLightDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDarkDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, ApplyDarkDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDarkDamage;
	ATTRIBUTE_ACCESSORS(UResonatorAttributeSet, BasicDarkDamage)

protected:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
