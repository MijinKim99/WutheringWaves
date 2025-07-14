// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "WWAttributeSet.generated.h"

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
class WUTHERINGWAVES_API UWWAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UWWAttributeSet();
	
	//현재 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, CurrentHp)
	//최대 HP
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, MaxHp)

	//적용 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyAttack;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, ApplyAttack)
	//기본 공격력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicAttack;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, BasicAttack)

	//적용 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData ApplyDefense;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, ApplyDefense)
	//기본 방어력
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData BasicDefense;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, BasicDefense)
	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, DamageTaken)
private:

protected:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
