// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseTypes/WWEnumType.h"
#include "WWBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

class UWWAbilitySystemComponent;
struct FGameplayTag;
UCLASS()
class WWCOPY_API UWWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
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
	
	UFUNCTION(BlueprintCallable, Category="FunctionLibrary", meta=(DisplayName="Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EWWConfirmType& OutType);
	
};
