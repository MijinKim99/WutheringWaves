// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/DataAssets/DataAsset_Startup.h"
#include "GameplayTagContainer.h"
#include "PlayerCharacterStartup.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInputAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories="InputTag"))
	FGameplayTag InputTag;

	//부여가능한 능력
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWWGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerCharacterStartup : public UDataAsset_Startup
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWWAbilitySystemComponent* ASC, int32 Level = 1) override;
	 
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta=(TitleProperty="InputTag"))
	TArray<FPlayerInputAbilitySet> PlayerStartupAbilitySets;

	
};
