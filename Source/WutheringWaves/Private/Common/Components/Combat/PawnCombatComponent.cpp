// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Components/Combat/PawnCombatComponent.h"

#include "Common/Attack/AttackCollisionBox.h"
#include "Common/Attack/AttackCollisionSphereProjectile.h"
#include "Common/ObjectPool/WWObjectPoolComponent.h"

void UPawnCombatComponent::OnHitTagetActor(AActor* HitActor)
{
	// 자식에서 구현
}

void UPawnCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	for (FAttackCollisionPoolInfo PoolInfo : AttackCollisionPools)
	{
		UWWObjectPoolComponent* NewPool;
		switch (PoolInfo.AttackCollisionType)
		{
		case EAttackCollisionType::Box:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionBox::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionBoxPool = NewPool;
			break;
		case EAttackCollisionType::SphereProjectile:
			NewPool = NewObject<UWWObjectPoolComponent>(
				GetOwningPawn(), UWWObjectPoolComponent::StaticClass());
			NewPool->PooledObjectClass = AAttackCollisionSphereProjectile::StaticClass();
			NewPool->PoolSize = PoolInfo.PoolSize;
			NewPool->PooledObjectLifeTime = PoolInfo.PooledObjectLifeTime;
			NewPool->RegisterComponent();
			AttackCollisionSphereProjectilePool = NewPool;
			break;
		default:
			break;
		}
	}
}

AAttackCollisionBox* UPawnCombatComponent::EnableAttackCollisionBoxFromPool()
{
	return Cast<AAttackCollisionBox>(AttackCollisionBoxPool->SpawnPooledObject(GetOwningPawn()));
}

AAttackCollisionSphereProjectile* UPawnCombatComponent::EnableAttackCollisionSphereProjectileFromPool()
{
	return Cast<AAttackCollisionSphereProjectile>(AttackCollisionSphereProjectilePool->SpawnPooledObject(GetOwningPawn()));
}

void UPawnCombatComponent::DeactivateAllPooledObjects()
{
	if (AttackCollisionBoxPool)
	{
		AttackCollisionBoxPool->DeactivateAllPooledObjects();
	}
	if (AttackCollisionSphereProjectilePool)
	{
		AttackCollisionSphereProjectilePool->DeactivateAllPooledObjects();
	}
}
