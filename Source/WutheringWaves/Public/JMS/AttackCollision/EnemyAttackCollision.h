// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "EnemyAttackCollision.generated.h"


class UProjectileMovementComponent;

// TODO: 적 하나만 공격 가능하므로 나중에 수정 필요
UCLASS(Abstract)
class WUTHERINGWAVES_API AEnemyAttackCollision : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyAttackCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Attack Collision")
	float CollisionDuration = 1.0f;
	void SetGameplayEffectSpecHandle(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool bIsProjectile = false;

	virtual void AttackAsProjectile(const FVector& TargetLocation, const FVector& BoxExtent);


protected:
	// Collision Setting
	FTimerHandle CollisionActivationTimerHandle;
	UFUNCTION()
	virtual void ResetCollision();
	FTransform InitialRelativeTransform;

	// Damage
	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	TSet<AActor*> HitTargetSet;
	void OnHitTargetActor(AActor* HitActor);

	FGenericTeamId InstigatorTeamId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
