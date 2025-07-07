// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "RootMotionModifier.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"
#include "JMS/Character/EnemyCharacter.h"

void UEnemyCombatComponent::SetAttackTransform(const FTransform& InTransform)
{
	AttackTransform = InTransform;
}


void UEnemyCombatComponent::EnableAttackCollisionForAWhile(const FEnemyAttackCollisionInfo& AttackCollisionInfo,
                                                           const FGameplayEffectSpecHandle& GameplayEffectSpecHandle)
{
	SetGameplayEffectSpecHandle(GameplayEffectSpecHandle);
	Cast<AEnemyCharacter>(GetOwningPawn())->SetAttackCollisionAtLocation(
		AttackTransform.GetTranslation(), AttackCollisionInfo.Duration, AttackCollisionInfo.BoxExtent);
}

void UEnemyCombatComponent::LaunchCollisionProjectile(const FEnemyAttackCollisionInfo& AttackCollisionInfo,
                                                      const FGameplayEffectSpecHandle& GameplayEffectSpecHandle)
{
}

void UEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 중복 검사
	if (HitTargetSet.Contains(HitActor))
	{
		return;
	}

	HitTargetSet.Add(HitActor);

	// GameplayEffectSpecHandle 적용
	UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(HitActor, GameplayEffectSpecHandleCache);

	// Gameplay Event 전달
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn()->GetInstigator();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, WWGameplayTags::Shared_Event_HitReact, Data);
}

void UEnemyCombatComponent::SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandleCache = InGameplayEffectSpecHandle;
}
