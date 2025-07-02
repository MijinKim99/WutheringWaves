// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AbilitySystem/PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitCurrentStamina(1.f);
	InitMaxStamina(1.f);
	
	InitApplyEnergyRegen(1.f);
	InitBasicEnergyRegen(1.f);
	
	InitApplyCriticalRate(1.f);
	InitBasicCriticalRate(1.f);
	
	InitApplyCriticalDamage(1.f);
	InitBasicCriticalDamage(1.f);
}
