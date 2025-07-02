// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "WWAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	bool TryActivateAbilityByTag(FGameplayTag Tag);

	
};
