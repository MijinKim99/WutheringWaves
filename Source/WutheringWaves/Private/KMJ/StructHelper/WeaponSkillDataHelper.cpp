// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/StructHelper/WeaponSkillDataHelper.h"

#include "VectorTypes.h"
#include "Common/WWStruct.h"
#include "WorldPartition/WorldPartitionBuilder.h"


FString UWeaponSkillDataHelper::WeaponSkillDataHelp(UPARAM(ref) FWeaponSkillData& SkillData)
{
	SkillData.SkillDescription = SkillData.GetFormattedDescription();
	//Debug::Print("Final Skill Description: "+SkillData.GetFormattedDescription());
	return SkillData.SkillDescription;
}

TArray<FInventory_Weapon> UWeaponSkillDataHelper::WeaponSortByStandard(UDataTable* WeaponData,
	TArray<FInventory_Weapon> WeaponItem, EWeaponSortStandard SortStandard)
{
	TArray<FInventory_Weapon> CopiedWeaponItems;
	CopiedWeaponItems.Append(WeaponItem);

	//무기 레어도 기준으로 정렬(무기 레어도 -> 무기 레벨)
	if (SortStandard == EWeaponSortStandard::Rarity)
	{
		//Debug::Print(TEXT("레어도 기준으로 정렬"));
		CopiedWeaponItems.Sort([WeaponData](const FInventory_Weapon& WeaponLeft, const FInventory_Weapon& WeaponRight)
		{
			FWeaponData* WeaponLeftData = WeaponData->FindRow<FWeaponData>(FName(WeaponLeft.RowIndex), "WeaponDataLeft");
			FWeaponData* WeaponRightData = WeaponData->FindRow<FWeaponData>(FName(WeaponRight.RowIndex), "WeaponDataRight");
			if (WeaponLeftData->WeaponRarity == WeaponRightData->WeaponRarity)
			{
				return WeaponLeft.WeaponCurrentLevel > WeaponRight.WeaponCurrentLevel;
			}
			return WeaponLeftData->WeaponRarity < WeaponRightData->WeaponRarity;
		});
	}
	else if (SortStandard == EWeaponSortStandard::Level)
	{
		//Debug::Print(TEXT("레벨 기준으로 정렬"));
		CopiedWeaponItems.Sort([WeaponData](const FInventory_Weapon& WeaponLeft, const FInventory_Weapon& WeaponRight)
		{
			FWeaponData* WeaponLeftData = WeaponData->FindRow<FWeaponData>(FName(WeaponLeft.RowIndex), "WeaponDataLeft");
			FWeaponData* WeaponRightData = WeaponData->FindRow<FWeaponData>(FName(WeaponRight.RowIndex), "WeaponDataRight");
			if (WeaponLeft.WeaponCurrentLevel == WeaponRight.WeaponCurrentLevel)
			{
				return WeaponLeftData->WeaponRarity < WeaponRightData->WeaponRarity;
			}
			return WeaponLeft.WeaponCurrentLevel > WeaponRight.WeaponCurrentLevel;
		});
	}
	
	return CopiedWeaponItems;
}
