// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "PlayerStateAttributeSet.generated.h"

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
class WUTHERINGWAVES_API UPlayerStateAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPlayerStateAttributeSet();
	
	//현재 스테미나
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UPlayerStateAttributeSet, CurrentStamina)
	//최대 스테미나
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPlayerStateAttributeSet, MaxStamina)

	//KMJ 0722
	UFUNCTION(BlueprintCallable, Category="Status")
	float GetStaminaPercent();

protected:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
