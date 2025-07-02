// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

class ATriggerBase;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	void SetAttackTransform(FTransform InTransform);
	
	
protected:
	FTransform AttackTransform;
	
};
