// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "RootMotionModifier.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "JMS/Character/EnemyCharacter.h"

void UEnemyCombatComponent::SetAttackTransform(const FTransform& InTransform)
{
	AttackTransform = InTransform;
}

FTransform UEnemyCombatComponent::GetAttackTransform()
{
	return AttackTransform;
}


void UEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}
