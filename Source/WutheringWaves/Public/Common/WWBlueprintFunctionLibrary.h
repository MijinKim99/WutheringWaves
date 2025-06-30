// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WWBlueprintFunctionLibrary.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	//BlueprintFunctionLibrary는 내부 접근이므로 public과 static으로 접근해야 함. 액터로 접근해 어빌리티 시스템 컴포넌트 가져오기
	//static UBaseAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void RemoveTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	/*
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary", meta=(DisplayName="Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);
	*/

	//static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* Actor);

	/*
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary"
		, meta=(DisplayName = "Get PawnCombatComponent From Actor", ExpandEnumAsExecs = "OutValid"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* Actor, EBaseValidType& OutValid);
	*/

	//피아 식별 헬퍼함수
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool IstargetPawnHostile(APawn* OwningPawn, APawn* TagetPawn);

	/*
	UFUNCTION(BlueprintPure, Category="FunctionLibrary", meta=(CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& ScFloat, float Level);
	*/

	/*
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Attacker, AActor* HitActor, float& OutAngleDiff);
	*/

	/*
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool IsValidBlock(AActor* Attacker, AActor* Defender);
	*/
};
