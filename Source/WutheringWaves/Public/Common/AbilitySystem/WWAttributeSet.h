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
	
	UWWAttributeSet();

public:
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, CurrentHp)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, MaxHp)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, Defence)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWWAttributeSet, DamageTaken)

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
