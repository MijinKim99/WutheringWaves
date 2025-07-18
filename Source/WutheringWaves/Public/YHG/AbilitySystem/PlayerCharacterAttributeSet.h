// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "PlayerCharacterAttributeSet.generated.h"

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
class WUTHERINGWAVES_API UPlayerCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPlayerCharacterAttributeSet();

	//현재 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, CurrentHp)
	//최대 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, MaxHp)

	//적용 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAttack;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyAttack)
	//기본 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAttack;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicAttack)

	//적용 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDefense;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyDefense)
	//기본 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDefense;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicDefense)
	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, DamageTaken)
	
	//적용 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyEnergyRegen;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyEnergyRegen)
	//기본 공명효율
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicEnergyRegen;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicEnergyRegen)

	//적용 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalRate;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyCriticalRate)
	//기본 크리티컬
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalRate;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicCriticalRate)

	//적용 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyCriticalDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyCriticalDamage)
	//기본 크리티컬피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicCriticalDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicCriticalDamage)
/*	
	//속성별 피해
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyFireDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyFireDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicFireDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicFireDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyIceDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyIceDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicIceDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicIceDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAirDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyAirDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAirDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicAirDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyElectricDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyElectricDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicElectricDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicElectricDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyLightDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyLightDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicLightDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicLightDamage)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDarkDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, ApplyDarkDamage)
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDarkDamage;
	ATTRIBUTE_ACCESSORS(UPlayerCharacterAttributeSet, BasicDarkDamage)
*/
protected:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
