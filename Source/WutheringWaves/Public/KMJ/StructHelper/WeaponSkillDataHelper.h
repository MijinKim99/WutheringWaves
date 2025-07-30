// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSkillDataHelper.generated.h"

struct FInventory_Weapon;
struct FWeaponData;
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

	UFUNCTION(BlueprintCallable)
	static TArray<FInventory_Weapon> WeaponSortByStandard(UPARAM(ref) UDataTable* WeaponData,
		UPARAM(ref) TArray<FInventory_Weapon> WeaponItem, EWeaponSortStandard SortStandard);
};
