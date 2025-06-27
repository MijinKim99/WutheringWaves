// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupBase.generated.h"

class UGameplayEffect;
class UWWAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WWCOPY_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level = 1);
protected:
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
};
