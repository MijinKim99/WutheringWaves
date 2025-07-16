// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Character/EliteEnemyCharacter.h"

#include "JMS/AbilitySystem/AttributeSet/EliteAttributeSet.h"

AEliteEnemyCharacter::AEliteEnemyCharacter()
{
	EliteAttributeSet = CreateDefaultSubobject<UEliteAttributeSet>(TEXT("EliteAttributeSet"));
}
