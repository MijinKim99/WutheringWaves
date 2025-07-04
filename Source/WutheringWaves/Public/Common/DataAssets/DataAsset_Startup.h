// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Startup.generated.h"

class UGameplayEffect;
class UWWAbilitySystemComponent;
class UWWGameplayAbility;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UDataAsset_Startup : public UDataAsset
{
	GENERATED_BODY()

public:

	//부여하는 ASC Level은 단계 1단계 기본부여
	virtual void GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level = 1);

protected:
	//부여받은 직후 활성화 되는 주어진 능력들
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UWWGameplayAbility>> ActivateOnGivenAbilities;

	//특정 조건에 대한 적중반응이나 사망같은 능력들
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UWWGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;

	//능력부여
	void GrantAbilities(const TArray<TSubclassOf<UWWGameplayAbility>> GAs, UWWAbilitySystemComponent* InASC, int32 Level);
};