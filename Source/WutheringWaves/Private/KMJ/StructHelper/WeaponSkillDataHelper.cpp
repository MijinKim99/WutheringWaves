// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/StructHelper/WeaponSkillDataHelper.h"

#include "Common/WWStruct.h"
#include "WorldPartition/WorldPartitionBuilder.h"


FWeaponSkillData UWeaponSkillDataHelper::WeaponSkillDataHelp(UPARAM(ref) FWeaponSkillData& SkillData)
{
	SkillData.SkillDescription = SkillData.GetFormattedDescription();
	//Debug::Print("Final Skill Description: "+SkillData.GetFormattedDescription());
	return SkillData;
}

FText UWeaponSkillDataHelper::ReplaceSkillNameInText(const FText& StatName, UPARAM(ref) FText& SkillDescription,
	int32 Index)
{
	// {SkillName0} 플레이스홀더 이름 만들기
	FString PlaceholderKeyString = FString::Printf(TEXT("StatName%d"), Index+1);
	FString PlaceholderKey(*PlaceholderKeyString);

	//Debug::Print("StatName: " + StatName.ToString() + "PlaceHolderKey: " + PlaceholderKey);

	// FFormatNamedArguments 사용 (정식 지원 타입)
	FFormatNamedArguments Args;
	Args.Add(PlaceholderKey, StatName); // 자동으로 FFormatArgumentValue로 래핑됨

	// 치환된 FText 반환
	return FText::Format(SkillDescription, Args);
}

FString UWeaponSkillDataHelper::ReplaceStatNumInString(const FString& StatNum, FString& SkillDescription,
	int32 Index)
{
	FString StatNumKey  = FString::Printf(TEXT("{StatNum%d}"), Index + 1);
	SkillDescription = SkillDescription.Replace(*StatNumKey, *StatNum);
	
	return SkillDescription;
}

float UWeaponSkillDataHelper::GetCurvedTableValue(UPARAM(ref) FWeaponSkillData& SkillData, EWeaponStatType StatName)
{
	return SkillData.InitializeStats(StatName);
}
