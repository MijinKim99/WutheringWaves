// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WWAttributeSet.h"
#include "CharacterAttributeSet.generated.h"
/**
 * 
 */
class IPawnUIInterface;

UCLASS()
class WWCOPY_API UCharacterAttributeSet : public UWWAttributeSet
{
	GENERATED_BODY()
public:
	UCharacterAttributeSet();
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, CurrentHp)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxHp)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, CurrentStamina)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, MaxStamina)

	
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, DamageTaken)
	
private:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
