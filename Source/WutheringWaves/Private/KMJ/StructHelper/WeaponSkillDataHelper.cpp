// Fill out your copyright notice in the Description page of Project Settings.


#include "KMJ/StructHelper/WeaponSkillDataHelper.h"

#include "Common/WWStruct.h"
#include "WorldPartition/WorldPartitionBuilder.h"


FString UWeaponSkillDataHelper::WeaponSkillDataHelp(UPARAM(ref) FWeaponSkillData& SkillData)
{
	SkillData.SkillDescription = SkillData.GetFormattedDescription();
	//Debug::Print("Final Skill Description: "+SkillData.GetFormattedDescription());
	return SkillData.SkillDescription;
}