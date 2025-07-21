 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ActivateAbilityAndWaitForEnd.generated.h"


class UGameplayAbility;
class UAbilitySystemComponent;
/**
 *  
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityEndDelegate);
UCLASS()
class WUTHERINGWAVES_API UActivateAbilityAndWaitForEnd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	static UActivateAbilityAndWaitForEnd* ActivateAbilityAndWaitForEnd(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayTag& AbilityTag);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityEndDelegate OnAbilityEnd;
	UPROPERTY(BlueprintAssignable)
	FOnAbilityEndDelegate OnAbilityCancelled;

	virtual void Activate() override;

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;
	UPROPERTY()
	FGameplayTag AbilityTag;

	UFUNCTION()
	void BroadCastOnAbilityEnd(UGameplayAbility* Ability);
	UFUNCTION()
	void BroadCastOnAbilityCancelled();
};
