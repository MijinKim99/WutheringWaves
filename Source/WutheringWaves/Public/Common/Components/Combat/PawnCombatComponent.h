// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/Components/WWPawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "Common/Interfaces/AttackCollisionPoolInterface.h"
#include "PawnCombatComponent.generated.h"

class UWWObjectPoolComponent;
class AAttackCollisionBox;
class AWWPooledObject;
class AWWObjectPool;

/**
 * 
 */
UENUM()
enum class EAttackCollisionType:uint8
{
	Box,
	SphereProjectile,
	BoxProjectile,
	Capsule,
};

USTRUCT()
struct FAttackCollisionPoolInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	EAttackCollisionType AttackCollisionType;
	UPROPERTY(EditAnywhere)
	int PoolSize = 20;
	UPROPERTY(EditAnywhere)
	float PooledObjectLifeTime = 20.0f;
};

UCLASS()
class WUTHERINGWAVES_API UPawnCombatComponent : public UWWPawnExtensionComponent, public IAttackCollisionPoolInterface
{
	GENERATED_BODY()
public:
	// 공격 처리
	virtual void OnHitTagetActor(AActor* HitActor);
	virtual void BeginPlay() override;

	//IAttackCollisionPoolInterface;
	virtual AAttackCollisionBox* EnableAttackCollisionBoxFromPool() override;
	virtual AAttackCollisionSphereProjectile* EnableAttackCollisionSphereProjectileFromPool() override;
	virtual AAttackCollisionBoxProjectile* EnableAttackCollisionBoxProjectileFromPool() override;
	virtual AAttackCollisionCapsule* EnableAttackCollisionCapsuleFromPool() override;
	
	UFUNCTION(BlueprintCallable, Category = "Attack Collision Pool")
	void DeactivateAllPooledObjects();

protected:
	//중복방지를 위한 배열
	TArray<AActor*> OverlappedActors;
	UPROPERTY(EditDefaultsOnly, Category = "Attack Collision Pool")
	TArray<FAttackCollisionPoolInfo> AttackCollisionPools;
private:
	UPROPERTY(VisibleAnywhere)
	UWWObjectPoolComponent* AttackCollisionBoxPool;
	UPROPERTY(VisibleAnywhere)
	UWWObjectPoolComponent* AttackCollisionSphereProjectilePool;
	UPROPERTY(VisibleAnywhere)
	UWWObjectPoolComponent* AttackCollisionBoxProjectilePool;
	UPROPERTY(VisibleAnywhere)
	UWWObjectPoolComponent* AttackCollisionCapsulePool;
};
