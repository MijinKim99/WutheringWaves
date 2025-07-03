// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/Component/EnemyCombatComponent.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"

void UEnemyCombatComponent::SetAttackTransform(const FTransform& InTransform)
{
	AttackTransform = InTransform;
}

void UEnemyCombatComponent::SpawnAttackCollision(const TSubclassOf<AEnemyAttackCollision>& AttackCollision,
                                                 const FGameplayEffectSpecHandle& GameplayEffectSpecHandle)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwningPawn();
	SpawnParams.Instigator = GetOwningPawn();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AEnemyAttackCollision* SpawnedAttackCollision = GetWorld()->SpawnActor<AEnemyAttackCollision>(AttackCollision, AttackTransform, SpawnParams);
	SpawnedAttackCollision->SetGameplayEffectSpecHandle(GameplayEffectSpecHandle);
	SpawnedAttackCollision->SetInstigator(GetOwningPawn());
	SpawnedAttackCollision->SetActorEnableCollision(true);
}
