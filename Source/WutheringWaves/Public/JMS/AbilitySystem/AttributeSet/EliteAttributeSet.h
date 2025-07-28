// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "EliteAttributeSet.generated.h"

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
class WUTHERINGWAVES_API UEliteAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UEliteAttributeSet();
	UPROPERTY(BlueprintReadOnly, Category="Stagger")
	FGameplayAttributeData MaxStagger;
	ATTRIBUTE_ACCESSORS(UEliteAttributeSet, MaxStagger)
	UPROPERTY(BlueprintReadOnly, Category="Stagger")
	FGameplayAttributeData CurrentStagger;
	ATTRIBUTE_ACCESSORS(UEliteAttributeSet, CurrentStagger)
	UPROPERTY(BlueprintReadOnly, Category="Stagger")
	FGameplayAttributeData StaggerDamageTaken;
	ATTRIBUTE_ACCESSORS(UEliteAttributeSet, StaggerDamageTaken)
	UPROPERTY(BlueprintReadOnly, Category="Parry")
	FGameplayAttributeData ParryDamageTaken;
	ATTRIBUTE_ACCESSORS(UEliteAttributeSet, ParryDamageTaken)
private:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	// TWeakInterfacePtr<IWWHUDSharedUIInterface> CachedHUDSharedUIInterface;
protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
