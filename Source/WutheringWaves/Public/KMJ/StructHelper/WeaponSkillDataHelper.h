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
	static FString WeaponSkillDataHelp(UPARAM(ref) FWeaponSkillData& SkillData);
};
