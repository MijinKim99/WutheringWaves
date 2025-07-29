// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "WWEnum.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WWBlueprintFunctionLibrary.generated.h"

class UGameplayEffect;
class UPawnCombatComponent;
struct FScalableFloat;
class UWWAbilitySystemComponent;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//BlueprintFunctionLibrary는 내부 접근이므로 public과 static으로 접근해야 함. 액터로 접근해 어빌리티 시스템 컴포넌트 가져오기
	static UWWAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void AddTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static void RemoveTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary")
	static FActiveGameplayEffectHandle ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	                                                                         const FGameplayEffectSpecHandle&
	                                                                         InGameplayEffectSpecHandle);

	UFUNCTION(BlueprintCallable, Category="FunctionLibrary",
		meta=(DisplayName="BP_HasTag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EWWConfirmType& OutType);


	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* Actor);


	UFUNCTION(BlueprintCallable, Category="FunctionLibrary"
		, meta=(DisplayName = "Get PawnCombatComponent From Actor", ExpandEnumAsExecs = "OutValid"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* Actor, EWWValidType& OutValid);


	//피아 식별 헬퍼함수
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* OwningPawn, APawn* TagetPawn);


	UFUNCTION(BlueprintPure, Category="FunctionLibrary", meta=(CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& ScFloat, float Level);

	//TODO: 방향 태그 추가 및 판별 로직 추가 필요
	/*
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Attacker, AActor* HitActor, float& OutAngleDiff);
	*/

	// 방어 시 각도에 따라 성공 여부 판별 하는 함수
	// 명조에는 방어가 없으므로 제거
	/*
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool IsValidBlock(AActor* Attacker, AActor* Defender);
	*/

	// Effect 적용 성공 여부를 반환
	// ASC가 설정되어 있지 않으면 Assert
	UFUNCTION(BlueprintPure, Category="FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor,
	                                                       const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void SeamlessTravel(UObject* WorldContextObject, const FString& MapReferencePath);

};
