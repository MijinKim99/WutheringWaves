// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSkillDataHelper.generated.h"

struct FWeaponSkillData;
/**
 * 
 */
UCLASS(Blueprintable)
class WUTHERINGWAVES_API UWeaponSkillDataHelper : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static FWeaponSkillData WeaponSkillDataHelp(UPARAM(ref) FWeaponSkillData& SkillData);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	static FText ReplaceSkillNameInText(const FText& StatName, UPARAM(ref) FText& SkillDescription, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Skill")
	static FString ReplaceStatNumInString(const FString& StatNum, UPARAM(ref)FString& SkillDescription, int32 Index);

	UFUNCTION(BlueprintCallable)
	static float GetCurvedTableValue(UPARAM(ref) FWeaponSkillData& SkillData, UPARAM(ref)EWeaponStatType StatName);
};
