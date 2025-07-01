// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Common/WWEnum.h"
#include "WWGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EWWAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Ability")
	UWWPawnCombatComponent* GetWWPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category="Ability")
	UWWAbilitySystemComponent* GetWWAbilitySystemComponentFromActorInfo() const;

	//ActiveGameplayEffectHandle 얻기
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category="Ability", meta =(DisplayName = "Apply Gameplay Effect Spec Handle To TargetActor",ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EWWSuccessType& OutSuccessType);
	
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;
	
	UPROPERTY(EditDefaultsOnly, Category = "BaseAbility")
	EWWAbilityActivationPolicy AbilityActivationPolicy = EWWAbilityActivationPolicy::OnTriggered;
};
