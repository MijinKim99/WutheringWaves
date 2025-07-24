// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AbilitySystem/Abilities/WWGameplayAbility.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"
#include "PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class AWWPlayerController;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerGameplayAbility : public UWWGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Ability")
	APlayerCharacter* GetPlayerCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category="Ability")
	AWWPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Ability")
	FGameplayEffectSpecHandle MakePlayerDamageGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect
		,float PlayerDamage, FGameplayTag AttackTypeTag, int32 ComboCount
	);
	
private:
	//영웅캐릭터의 정보를 가지고 있다면 캐시 (TWeakObjectPtr는 공유 참조가 존재하지 않을 때 객체를 자동으로 해제(GC)) - 약한 포인터
	TWeakObjectPtr<APlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<AWWPlayerController> CachedPlayerController;
};
