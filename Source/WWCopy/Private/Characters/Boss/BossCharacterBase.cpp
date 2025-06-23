// Fill out your copyright notice in the Description page of Project Settings.


#include "WWCopy/Public/Characters/Boss/BossCharacterBase.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"

ABossCharacterBase::ABossCharacterBase()
{
}

void ABossCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

