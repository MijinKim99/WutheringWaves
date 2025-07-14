// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/AbilitySystem/AttributeSet/EnemyAttributeSet.h"
#include "EliteAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEliteAttributeSet : public UEnemyAttributeSet
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
private:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
