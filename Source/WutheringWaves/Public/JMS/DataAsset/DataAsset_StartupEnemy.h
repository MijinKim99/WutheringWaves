// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/DataAssets/DataAsset_Startup.h"
#include "DataAsset_StartupEnemy.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UDataAsset_StartupEnemy : public UDataAsset_Startup
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UEnemyGameplayAbility>> EnemyCombatAbilities;
};
