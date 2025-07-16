// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/Character/EnemyCharacter.h"
#include "EliteEnemyCharacter.generated.h"

class UEliteAttributeSet;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEliteEnemyCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEliteEnemyCharacter();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEliteAttributeSet* EliteAttributeSet;
	
	
};
